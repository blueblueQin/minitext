#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "head.h"


int inputProcess(char c,struct eroww* erow,int *startRow,int *x,int *y){

    
    if(c == 27){//上下右左
        scanf("%c",&c);
        if(c == 91){
            scanf("%c",&c);
            if(c == 65){
                printf("\x1B[1A");
            }
            else if(c == 66){
                printf("\x1B[1B");
            }
            else if(c == 67){
                printf("\x1B[1C");
            }
            else if(c == 68){
                printf("\x1B[1D");
            }
            else if(c == 72){//home
                printf("\x1B[1G");
            }
            else if(c == 70){//end
                printf("\x1B[%dC",92);
            }
            else if(c == 53){//pageUp
                scanf("%c",&c);
                if(c == 126) printf("\033[H");
            }
            else if(c == 54){//pageDn
                scanf("%c",&c);
                if(c == 126) printf("\x1B[%dB", 10);
            }
        }
    }
    else if(c == 13){//回车
        printf("\x1B[%dE", 1);
        //printf("\x1B[%dG", 1);
    }
    else if(c == 127){//回退
        printf("\x1B[1D");
    }
    else if(c == 9){//tab
        printf("    ");
    }
    else if(c == 32){
        printf(" ");
    }
    else printf("%c",c);
    return 0;
}
/*
int bufferProcess(char c){
            if(c == 65){
                if(*y>1) *y-=1;
            }
            else if(c == 66){
                if(*y) *y+=1;
            }
            else if(c == 67){
                if(*x) *x+=1;
            }
            else if(c == 68){
                if(*x>1) *x-=1;
            }
            else if(c == 72){//home
                *x = 1;
            }
            else if(c == 70){//end
                int i=0;
                while(buffer[i]){
                    i++;
                }
                *x = i;
            }
            else if(c == 53){//pageUp
                scanf("%c",&c);
                if(c == 126) printf("\x1B[%dA", 1);
            }
            else if(c == 54){//pageDn
                scanf("%c",&c);
                if(c == 126) printf("\x1B[%dB", 1);
            }
    return 0;
}
int bufferAdd(char c){
    return 0;
}
*/
