#include "MySector.h"

MySector::MySector(int proportion,QString pa_string,QString ca_string,QWidget *parent)
    : QWidget(parent),
      path_str(pa_string),
      capa_str(ca_string),
      m_FrontColor(Qt::red),
      m_BackColor(Qt::white),
      inRadious(50),
      outRadious(52),
      offset(proportion * 3.6)
{
//    this->setFixedSize(200,200);
/*todo
 * 比例图半径为动态实现
 * date:2018/03/23
 * author:daihualei
*/

}

MySector::~MySector()
{
    
}

void MySector::paintEvent(QPaintEvent *)
{

    QRectF inRectF(-inRadious,-inRadious,inRadious*2,inRadious*2);
    QRectF outRectF(-outRadious,-outRadious,outRadious*2,outRadious*2);


    QPainter p(this);
    p.translate(width()/2, height()/2);
    p.setRenderHint(QPainter::Antialiasing);

    p.setPen(Qt::gray);
    p.setBrush(m_BackColor);
    p.drawEllipse(inRectF);

    m_FrontColor.setAlpha(255);
    p.setBrush(m_FrontColor);
    p.drawPie(outRectF,0*16,(offset)*16);

    p.save();
    QString valueStr = path_str + "\n" + capa_str + "\n"
            + QString("%1%").arg(QString::number(1.0*(offset)/360*100,'f',0));
    QFont font = p.font();
    font.setBold(true);
    p.setPen(Qt::black);
    p.drawText(inRectF,Qt::AlignCenter,valueStr);
    p.restore();

}
