#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<QList>

typedef struct
{
    char user[20];
    char pid[20];
    char cpu[20];
    char mem[20];
    char stat[20];
    char command[100];
}PROCESS_INFO;

QList<PROCESS_INFO> get_process_info();
