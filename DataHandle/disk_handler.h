#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<QList>

typedef struct
{
    char file_system[20];
    char capacity[20];
    char used[20];
    char available[20];
    char rate[20];
    char path[20];
}DISK_INfO;

QList<DISK_INfO> get_disk_info();
