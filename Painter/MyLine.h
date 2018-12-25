#ifndef MYLINE_H
#define MYLINE_H

#include<QWidget>
#include<QPainter>
#include<QTimer>
#include<QPoint>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include<QDesktopWidget>
#include<QApplication>
#include<QPaintEvent>
#include<QDebug>
#include<QList>

#include "unistd.h"


class MyLine : public QWidget
{
    Q_OBJECT
    
public:
    MyLine(QWidget *parent = 0);
    ~MyLine();
    void updateLine(double,double);

protected:
    void paintEvent(QPaintEvent *);


private:
    int m_rate;
    double m_total;

    QList<int> m_y_int_list;
    QPainterPath m_path;
};

#endif // MYLINE_H
