#include "MyLine.h"

MyLine::MyLine(QWidget *parent)
    : QWidget(parent),
      m_rate(0),
      m_total(0.0)
{
    this->setFixedSize(540,100);

    m_path.moveTo(0,this->height());

    for(int i =0; i<= this->width()/10; i++)
    {
        m_y_int_list.append(this->height());
    }
    for(int j=0; j<m_y_int_list.size(); j++)
    {
        m_path.lineTo(QPoint(j*10,m_y_int_list.at(j)));
    }
}

MyLine::~MyLine()
{
    
}

void MyLine::updateLine(double rate,double total)
{
    m_rate = rate*100;
    m_total = total;
    m_path -=m_path;
    m_path.moveTo(0,this->height());
    m_y_int_list.removeFirst();
    m_y_int_list.append((1-rate)*this->height());

    for(int j=0; j<m_y_int_list.size(); j++)
    {
        m_path.lineTo(QPoint(j*10,m_y_int_list.at(j)));
    }
//    qDebug()<<m_y_int_list;
//    qDebug()<<"[0]:"<<m_y_int_list.at(m_y_int_list.size()-1);
    update();
}

void MyLine::paintEvent(QPaintEvent *)
{

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(Qt::red,2));
    p.drawPath(m_path);
    p.save();
    p.setPen(QPen(Qt::black));
    p.drawText(QRectF(0,0,this->width(),this->height()),QString("%1%")
               .arg(QString::number(m_rate,'f',0))+"/"+QString::number(m_total)+"G");
    p.drawRect(QRectF(0,0,this->width(),this->height()));
    p.drawText(QRectF(0,0,this->width(),this->height()),Qt::AlignRight|Qt::AlignBottom,"0 ");
    p.restore();
}

