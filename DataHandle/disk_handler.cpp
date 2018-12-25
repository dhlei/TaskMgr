#include"disk_handler.h"

QList<DISK_INfO> get_disk_info()
{
    FILE *fd;
    char f[20],c[20],u[20],a[20],r[20],p[20];
    char buff[256];
    QList<DISK_INfO> Disk_List;
    DISK_INfO disk_info;

    fd = popen("df -h","r");
    fgets(buff,sizeof(buff),fd);
    memset(buff,0,sizeof(buff));
    while((fgets(buff,sizeof(buff),fd)) != NULL)
    {
        sscanf(buff,"%s %s %s %s %s %s",f,c,u,a,r,p);
        strcpy(disk_info.file_system, f);
        strcpy(disk_info.capacity, c);
        strcpy(disk_info.used, u);
        strcpy(disk_info.available, a);
        strcpy(disk_info.rate, r);
        strcpy(disk_info.path, p);
        memset(buff,0,sizeof(buff));

        Disk_List.append(disk_info);
    }

    return Disk_List;
}


