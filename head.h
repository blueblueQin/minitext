#ifndef head.h
#define head.h

#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int inputProcess(char c , struct eroww* erow , int x[4] );
int bufferProcess(char c);
int bufferAdd(char c);
int reNew(struct eroww* erow , int x[4] , char* name);

typedef struct eroww {
    char* data;
    int length;           // 邻接表指针
} erow;

#endif 