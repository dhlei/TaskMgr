#ifndef MYCOLUMN_H
#define MYCOLUMN_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include<QBrush>
#include<QApplication>
#include<QDesktopWidget>
#include<QPaintEvent>


class MyColumn : public QWidget
{
    Q_OBJECT
    
public:
    MyColumn(int rate = 0,QString name= "----",QWidget *parent = 0);
    ~MyColumn();

    int offset;

protected:
    void paintEvent(QPaintEvent *);

private:
    QBrush m_BackBrush;
    QString m_name;

public slots:
    void timeUpDate(double);
};

#endif // MYCOLUMN_H
