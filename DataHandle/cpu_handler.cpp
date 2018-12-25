#include "cpu_handler.h"

QList<CPU_INFO> get_cpus_status()
{
    FILE *fd;
    char buff[256];
    QList<CPU_INFO> Cpu_List;
    CPU_INFO cpu_occupy;

    fd = fopen("/proc/stat","r");

    while(fgets(buff,sizeof(buff),fd))
    {
        sscanf(buff,"%s %u %u %u %u %u %u %u",cpu_occupy.name,&cpu_occupy.user,
               &cpu_occupy.nice,&cpu_occupy.sys,&cpu_occupy.idle,&cpu_occupy.iowait,
               &cpu_occupy.irq,&cpu_occupy.softirq);
        if(QString(cpu_occupy.name) == "intr")
        {
            break;
        }
        Cpu_List.append(cpu_occupy);
        memset(buff,0,sizeof(buff));
    }
    fclose(fd);
    return Cpu_List;
}

QList<double> cal_cpus_occupy(QList<CPU_INFO> o, QList<CPU_INFO> n)
{
    double od, nd;
    double id, sd;
    double cpu_use_rate;
    QList<double> cpus_rate_list;

    for(int i = 0; i < o.size(); i ++)
    {
        od = (double)(o[i].user + o[i].nice
                      + o[i].sys + o[i].idle + o[i].irq + o[i].softirq + o[i].iowait);
        nd = (double)(n[i].user + n[i].nice
                      + n[i].sys + n[i].idle + n[i].irq + n[i].softirq + n[i].iowait);

        id = (double)(o[i].idle);
        sd = (double)(n[i].idle);

        if((id - sd) != 0)
        {
            cpu_use_rate = 1 - (sd - id)/(nd - od);
        }
        else
        {
            cpu_use_rate = 0;
        }
        cpus_rate_list.append(cpu_use_rate);
    }
    return cpus_rate_list;
}

QList<double> get_cpus_rate()
{

    QList<double> cpu_rate_list;
    QList<CPU_INFO> cpus_status_1;
    QList<CPU_INFO> cpus_status_2;

    cpus_status_1 = get_cpus_status();

    sleep(2);

    cpus_status_2 = get_cpus_status();

    cpu_rate_list = cal_cpus_occupy(cpus_status_1,cpus_status_2);

    return cpu_rate_list;
}

QList<QString> get_cpus_name()
{
    QList<QString> cpus_name_lsit;
    QList<CPU_INFO> c = get_cpus_status();
    for(int i = 0; i < c.size(); i ++)
    {
        cpus_name_lsit.append(QString(c.at(i).name));
    }
    return cpus_name_lsit;
}
