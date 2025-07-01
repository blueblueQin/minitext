#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "head.h"
#define TOTALROW 28

int reNew(struct eroww* erow,int startRow){
    printf("\033[2J\033[H");
    for(int i=startRow; i < TOTALROW + startRow - 1 ;i++){
        printf("%s\n",erow[i].data);
    }
    printf("\033[H");
    return 0;
}