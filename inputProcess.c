#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "head.h"
#define TOTALROW 27

int inputProcess(char c , struct eroww* erow , int x[4] ){

    
    if(c == 27){//上下右左
        scanf("%c",&c);
        if(c == 91){
            scanf("%c",&c);
            if(c == 65){
                printf("\x1B[1A");
                if(x[1]>0) x[1]--;
            }
            else if(c == 66){
                if(x[1]<TOTALROW) {
                    printf("\x1B[1B");
                    x[1]++;
                }
                else x[3]+=1;
            }
            else if(c == 67){
                
                if(x[0]<erow[x[1]].length) {
                    x[0]+=1;
                    printf("\x1B[1C");
                }
                else {
                    x[1]+=1;
                    printf("\x1B[%dE", 1);
                }
            }
            else if(c == 68){
                //printf("\x1B[1D");
                if(x[0]>0) {
                    x[0]-=1;
                    printf("\x1B[1D");
                }
                else {
                    if(x[1]>0) x[1]-=1;
                    printf("\x1B[%dF", 1);
                    printf("\x1B[%d`",erow[x[1]].length);
                }
            }
            else if(c == 72){//home
                printf("\x1B[1G");
                x[0] = 0;
            }
            else if(c == 70){//end
                x[0] = erow[x[1]].length;
                printf("\x1B[%d`",erow[x[1]].length);
            }
            else if(c == 53){//pageUp
                scanf("%c",&c);
                if(c == 126) {
                    //printf("\033[H");
                    if((x[3]-=10)<0) x[3]=0;
                }
            }
            else if(c == 54){//pageDn
                scanf("%c",&c);
                if(c == 126) if(x[3]+TOTALROW<x[2]) x[3]+=10;
                //printf("\x1B[%dB", 10);
            }
        }
    }
    else if(c == 13){//回车
        //printf("\x1B[%dE", 1);
    }
    else if(c == 127){//回退
        //printf("\x1B[1D");
    }
    else if(c == 9){//tab
        //printf("    ");
    }
    else if(c == 32){
        //printf(" ");
    }
    else //printf("%c",c);
    return 0;
}

