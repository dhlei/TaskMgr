#include"process_handler.h"

QList<PROCESS_INFO> get_process_info()
{
    FILE *fd;
    char user[20],pid[20],cpu[20],mem[20],stat[20],command[100];
    char vsz[20],rss[20],tty[20],start[20],time[20];
    char buff[384];
    QList<PROCESS_INFO> process_info_list;
    PROCESS_INFO process_info;

    fd = popen("ps -ux","r");
    fgets(buff,sizeof(buff),fd);
    memset(buff,0,sizeof(buff));
    while((fgets(buff,sizeof(buff),fd)) != NULL)
    {
        sscanf(buff,"%s %s %s %s %s %s %s %s %s %s %s",user,pid,cpu,mem,vsz,rss,tty,stat,start,time,command);
        strcpy(process_info.user, user);
        strcpy(process_info.pid, pid);
        strcpy(process_info.cpu, cpu);
        strcpy(process_info.mem, mem);
        strcpy(process_info.stat, stat);
        strcpy(process_info.command, command);
        memset(buff,0,sizeof(buff));

        process_info_list.append(process_info);
    }

    return process_info_list;
}
