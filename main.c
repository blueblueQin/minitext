#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

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
    options.c_iflag &= ~(IXON | IXOFF | IXANY | BRKINT | INPCK | ISTRIP); // 关闭软件流控
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // 关闭规范模式
    options.c_oflag &= ~OPOST; // 关闭输出处理
    

    // 设置超时
    options.c_cc[VMIN]  = 1;
    options.c_cc[VTIME] = 1;

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

int main(){
    int fd=0;
    for (int i=0; i<12; i++){
        fd = STDIN_FILENO; //open("/dev/ttyS1", O_RDWR | O_NOCTTY);
        if (fd < 0) {
            continue;
        }
    }
    if (fd < 0) {
            perror("open serial port error");
            return -1;
        }

    if (enableRawMode(fd) == 0) {
        printf("Serial port configured successfully\n");
    }

    char c = 0;
    while(1){
        scanf("%c", &c);
        printf("%d",c);
        if(c == 'q') break;
    }

    if (disableRawMode(fd) == 0) {
        printf("Serial port recovery successfully\n");
    }
    close(fd);


    return 0;
}