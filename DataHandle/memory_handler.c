#include "memory_handler.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

/*
 * memTotale 总内存
 * memFree  系统空闲内存
 * memAvailable 空闲内存
*/

MEMORY_PACK *get_memory_info()
{
    FILE *fd;
    char buff[256];
    double total_mem;
    double use_mem_rate;

    MEMORY_INFO *o = (MEMORY_INFO *)malloc(sizeof(MEMORY_INFO));
    MEMORY_PACK *p = (MEMORY_PACK *)malloc(sizeof(MEMORY_PACK));

    fd = fopen("/proc/meminfo","r");
    fgets(buff,sizeof(buff),fd);
    sscanf(buff,"%s %lu %s\n",o->name,&o->size,o->unit);
    total_mem = o->size;
    memset(buff,0,sizeof(buff));
    fgets(buff,sizeof(buff),fd);
//    sscanf(buff,"%s %lu %s\n",o->name,&o->size,o->unit);
    memset(buff,0,sizeof(buff));
    fgets(buff,sizeof(buff),fd);
    sscanf(buff,"%s %lu %s\n",o->name,&o->size,o->unit);
    use_mem_rate = (1 - o->size / total_mem)*100;
    total_mem = total_mem/(1024*1024);
    p->total = total_mem;
    p->use_rate = use_mem_rate;

    fclose(fd);
    return p;
}
