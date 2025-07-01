#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "head.h"
#define TOTALROW 27

int reNew(struct eroww* erow,int startRow,int x,int y,int rows,char* name){
    printf("\033[2J\033[H");
    for(int i=startRow; i < TOTALROW + startRow - 1 ;i++){
        if(erow[i].data) printf("%s\n",erow[i].data);
    }
    printf("\033[H");

    for(int i=0;i<25;i++){
        if(name[i]) i++;
        else continue;
        if(i>20) name = "No Name";
    }    
    printf("Name:%s row:%d//%d\n",name,y,rows);
    return 0;
}