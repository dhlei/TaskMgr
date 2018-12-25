#ifndef TASKMGR_H
#define TASKMGR_H

#include <QWidget>
#include <QTimer>
#include <QList>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "DataHandle/disk_handler.h"
#include "Painter/MySector.h"
#include "DataHandle/memory_handler.h"
#include "Painter/MyLine.h"
#include "DataHandle/cpu_handler.h"
#include "Painter/MyColumn.h"

#include <QThread>
#include <QMutex>

#include "DataHandle/process_handler.h"
#include <QTableWidget>

namespace Ui {
class TaskMgr;
}

class MyThread;

class TaskMgr : public QWidget
{
    Q_OBJECT

public:
    explicit TaskMgr(QWidget *parent = 0);
    ~TaskMgr();

private slots:
    void updateMemSlot();
    void updateCpuSlot(QList<double>);

private:
    Ui::TaskMgr *ui;
    QTimer *m_timer;

    QList<DISK_INfO> m_disk_info_list;
    QList<int> m_disk_rate_list;
    QGridLayout *m_disk_glayout;
    QString disk_str;
    int m_disk_count;

    MyLine *m_mem_line_widget;
    QVBoxLayout *m_mem_vblayout;

    QList<double> m_cpus_rate_list;
    QList<QString> m_cpus_name_list;
    QList<MyColumn *> m_cpu_widget_list;
    QHBoxLayout *m_cpu_layout;

    MyThread *m_thread;

    QList<PROCESS_INFO> m_process_info_list;
    QTableWidget *m_tablewidget;
    QStringList header;
    QVBoxLayout *m_process_layout;

};

class MyThread:public QThread
{
    Q_OBJECT

public:
    MyThread(QObject *par = 0);
    ~ MyThread();
    void run();

private:
    QList<double> cpu_data_list;
    QMutex m_lock;
    bool m_quit_flag;

signals:
    void get_data_sig(QList<double>);

public slots:
    void stop_immediately();
};

#endif // TASKMGR_H
