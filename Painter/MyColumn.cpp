#include "MyColumn.h"

MyColumn::MyColumn(int rate,QString name,QWidget *parent)
    : QWidget(parent),
      offset(rate),
      m_name(name),
      m_BackBrush(Qt::black,Qt::HorPattern)
{
    this->setStyleSheet("background:black");
}

MyColumn::~MyColumn()
{
    
}

void MyColumn::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.save();
    p.setBrush(Qt::green);
    p.setPen(Qt::NoPen);
    p.drawRect(0,this->height() - offset - 20,this->width(),offset);
    p.restore();
    p.setBrush(m_BackBrush);
    p.drawRect(0,0,this->width() - 1,this->height()-1 - 20);

    p.save();
    QString valueStr = m_name+" : "+QString("%1%").arg(QString::number(offset,'f',0));
    QFont font = p.font();
    font.setBold(true);
    p.setPen(Qt::black);
    p.drawText(0,0,this->width(),this->height(),Qt::AlignHCenter|Qt::AlignBottom,valueStr);
    p.restore();

}

void MyColumn::timeUpDate(double rate)
{
    offset = this->height() * rate / 100;
    update();

}
