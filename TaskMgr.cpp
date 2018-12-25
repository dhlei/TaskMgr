#include "TaskMgr.h"
#include "ui_TaskMgr.h"

TaskMgr::TaskMgr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskMgr)
{
    ui->setupUi(this);
    this->setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(),this->height());

    m_timer = new QTimer(this);

    /*
     * disk
    */
    m_disk_glayout = new QGridLayout();
    m_disk_info_list = get_disk_info();

    for(int i = 0 ;i < m_disk_info_list.size() ;i++)
    {
        disk_str = QString(m_disk_info_list.at(i).rate);
        int d = disk_str.lastIndexOf("%");
        disk_str = disk_str.mid(0,d);
        m_disk_rate_list.append(disk_str.toInt());
    }

    m_disk_count = m_disk_rate_list.size();
    int line = m_disk_count / 4;
    if((m_disk_count % 4) != 0)
    {
        line ++;
    }

    for(int j = 0 ;j < m_disk_rate_list.size() ;j++ )
    {
        MySector *disk_sector
                = new MySector(m_disk_rate_list.at(j),
                               QString(m_disk_info_list.at(j).path),
                               m_disk_info_list.at(j).capacity);
        disk_sector->setFixedSize(this->width()/4,this->height()/line);
        m_disk_glayout->addWidget(disk_sector,j/4+1,j%4+1);
    }
    ui->disk_tab->setLayout(m_disk_glayout);

    /*
     * memory
    */
    m_mem_vblayout = new QVBoxLayout();
    m_mem_line_widget = new MyLine();
    m_mem_vblayout->addWidget(m_mem_line_widget);

    connect(m_timer,SIGNAL(timeout()),this,SLOT(updateMemSlot()));

    ui->mem_groupBox->setLayout(m_mem_vblayout);

    /*
     * cpu
    */
    m_cpus_rate_list = get_cpus_rate();
    m_cpus_name_list = get_cpus_name();
//    qDebug()<<m_cpus_rate_list;
    m_cpu_layout = new QHBoxLayout();

    for(int i = 0; i < m_cpus_rate_list.size();i++)
    {
        MyColumn *cpu_widget = new MyColumn(m_cpus_rate_list.at(i)*100,m_cpus_name_list.at(i));
        m_cpu_widget_list.append(cpu_widget);
    }
    for(int j=0;j<m_cpu_widget_list.size();j++)
    {
        m_cpu_layout->addWidget(m_cpu_widget_list.at(j));
    }

    //开子进程读数据，解决界面假死
    m_thread = new MyThread(this);
    connect(m_thread,SIGNAL(get_data_sig(QList<double>)),
            this,SLOT(updateCpuSlot(QList<double>)));
    m_thread->start();

    ui->cpu_groupBox->setLayout(m_cpu_layout);

    /*
     *
     *进程
     *
    */
    m_process_layout = new QVBoxLayout();
    m_process_info_list = get_process_info();
    for(int i =0;i<m_process_info_list.size();i++)
//    qDebug()<<m_process_info_list.at(i).command;

    header<<"进程名"<<"%cpu"<<"%mem"<<"用户"<<"PID"<<"状态";
    m_tablewidget = new QTableWidget(m_process_info_list.size(),6);
    m_tablewidget->setHorizontalHeaderLabels(header);
    m_tablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tablewidget->horizontalHeader()->resizeSection(0,290);
    m_tablewidget->horizontalHeader()->resizeSection(1,50);
    m_tablewidget->horizontalHeader()->resizeSection(2,50);
    m_tablewidget->horizontalHeader()->resizeSection(3,50);
    m_tablewidget->horizontalHeader()->resizeSection(4,50);
    m_tablewidget->horizontalHeader()->resizeSection(5,50);

    for(int i =0;i<m_process_info_list.size();i++)
    {
        QTableWidgetItem *item1 = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
        QTableWidgetItem *item3 = new QTableWidgetItem();
        QTableWidgetItem *item4 = new QTableWidgetItem();
        QTableWidgetItem *item5 = new QTableWidgetItem();
        QTableWidgetItem *item6 = new QTableWidgetItem();
        item1->setText(m_process_info_list.at(i).command);
        item2->setText(m_process_info_list.at(i).cpu);
        item3->setText(m_process_info_list.at(i).mem);
        item4->setText(m_process_info_list.at(i).user);
        item5->setText(m_process_info_list.at(i).pid);
        item6->setText(m_process_info_list.at(i).stat);

        m_tablewidget->setItem(i,0,item1);
        m_tablewidget->setItem(i,1,item2);
        m_tablewidget->setItem(i,2,item3);
        m_tablewidget->setItem(i,3,item4);
        m_tablewidget->setItem(i,4,item5);
        m_tablewidget->setItem(i,5,item6);

    }

   m_process_layout->addWidget(m_tablewidget);
   ui->progress_tab->setLayout(m_process_layout);


   m_timer->start(100);

}

TaskMgr::~TaskMgr()
{
    m_thread->stop_immediately();
    m_thread->wait();
    delete ui;
}

void TaskMgr::updateMemSlot( )
{
    MEMORY_PACK *m = get_memory_info();
    m_mem_line_widget->updateLine(m->use_rate/100.0,m->total);

}

void TaskMgr::updateCpuSlot(QList<double> list)
{
    int ii = 0;
    m_cpus_rate_list = list;
    foreach (MyColumn *widget, m_cpu_widget_list)
    {
        widget->offset = m_cpus_rate_list.at(ii++)*100;
        widget->update();
    }
    ii =0;
}

MyThread::MyThread(QObject *par):QThread(par),m_quit_flag(false)
{
    qDebug()<<"thread id:"<<this->currentThreadId();
}

MyThread::~MyThread()
{

}

void MyThread::run()
{
    while(1)
    {
        m_lock.lock();
        cpu_data_list = get_cpus_rate();
        emit get_data_sig(cpu_data_list);
        m_lock.unlock();

        if(m_quit_flag)
        {
            return;
        }
        qDebug()<<"son thread id:"<<this->currentThreadId();
        msleep(200);
    }

}

void MyThread::stop_immediately()
{
    m_quit_flag = true;
}
