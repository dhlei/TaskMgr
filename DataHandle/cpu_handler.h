#ifndef CPU_HANDLER_H
#define CPU_HANDLER_H

#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <QList>
#include <QString>

typedef struct
{
    char name[20];
    unsigned int user;
    unsigned int nice;
    unsigned int sys;
    unsigned int idle;
    unsigned int iowait;
    unsigned int irq;
    unsigned int softirq;
}CPU_INFO;



QList<CPU_INFO> get_cpus_status();

QList<double> cal_cpus_occupy(QList<CPU_INFO> ,QList<CPU_INFO>);

QList<double> get_cpus_rate();

QList<QString> get_cpus_name();

#endif //CPU_HANDLER_H
