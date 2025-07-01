#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "head.h"
#define ROWS 150

struct termios preoption;
int enableRawMode(int fd){
    struct termios options;

    // 获取当前配置
    if (tcgetattr(fd, &options) != 0) {
        perror("tcgetattr error");
        return -1;
    }
    
    memcpy(&preoption, &options, sizeof(struct termios));


    // 设置波特率
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    // 配置控制模式
    options.c_cflag |= (CLOCAL | CREAD); // 本地连接, 使能接收
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8; // 8 数据位
    options.c_cflag &= ~PARENB; // 无校验
    options.c_cflag &= ~CSTOPB; // 1 停止位

    // 配置输入输出模式
    options.c_iflag &= ~(IXON | IXOFF | IXANY | BRKINT | INPCK | ISTRIP | IGNBRK 
                    | PARMRK | ISTRIP| INLCR | IGNCR | ICRNL ); // 关闭软件流控
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG | IEXTEN | ECHONL); // 关闭规范模式
    options.c_oflag &= ~OPOST; // 关闭输出处理
    

    // 设置超时
    options.c_cc[VMIN]  = 1;
    options.c_cc[VTIME] = 5;

    // 刷新缓冲区并应用配置
    tcflush(fd, TCIFLUSH);
    if (tcsetattr(fd, TCSANOW, &options) != 0) {
        perror("tcsetattr error");
        return -1;
    }

    return 0;

}

int disableRawMode(int fd){
    tcflush(fd, TCIFLUSH);
    if (tcsetattr(fd, TCSANOW, &preoption) != 0) {
        perror("tcsetattr error");
        return -1;
    }
}


int init(int fd){
    
    printf("\033[2J\033[H");
    fd = STDIN_FILENO;
    if (fd < 0) {
            perror("open serial port error");
            return -1;
        }

    if (enableRawMode(fd) == 0) {
    }
    return 0;
}
int finish(int fd){
    printf("\033[2J\033[H");
    if (disableRawMode(fd) == 0) {
    }
    close(fd);
    return 0;
}

int main(int argc, char *argv[]){
    struct eroww erow[ROWS];
    char *name;
    int linenumber=0;
    if(argv[1]) {
        name = argv[1];
        FILE *inputfile = fopen(name, "r");
        if (inputfile == NULL) {
            perror("Failed to open file \n");
            return 0;
        }
        char line[1024];
        while (fgets(line, sizeof(line), inputfile)){
            if(line){
                strcpy(erow[linenumber].data,line);
                linenumber++;
                continue;
            }
        
        }
    }
    else linenumber=1;



    int fd;
    int x,y;
    init(fd);
    
    char c = 0;
    int startRow = 0;
    while(1){
        reNew(erow,startRow,x,y,linenumber,name);
        scanf("%c", &c);
        inputProcess(c,erow,&startRow,&x,&y);

        if(c == 'q') break;
    }

    
    finish(fd);
    return 0;
}

