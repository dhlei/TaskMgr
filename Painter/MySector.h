#ifndef MYSECTOR_H
#define MYSECTOR_H

/*扇形显示封装类*/

#include <QWidget>
#include<QTimer>
#include<QPainter>
#include<QFont>
#include<QString>
#include<QPaintEvent>
#include<QDebug>
#include<QColor>
#include<QString>

class MySector : public QWidget
{
    Q_OBJECT
    
public:
    MySector(int proportion = 0,QString pa_string = " ",QString ca_string = " ",QWidget *parent = 0 );
    ~MySector();

protected:
    void paintEvent(QPaintEvent *);

private:
//    QTimer *m_Timer;
    QColor m_FrontColor;
    QColor m_BackColor;
    int inRadious;
    int outRadious;
    int offset;
    QString path_str;
    QString capa_str;

};

#endif // MYSECTOR_H
