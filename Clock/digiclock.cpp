#include "digiclock.h"
#include <QTimer>
#include <QTime>
#include <QMouseEvent>

DigiClock::DigiClock(QWidget* parent): QLCDNumber (parent)
{
    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::blue);
    setPalette(p);  //这里应该是省略了this->
    setWindowFlag(Qt::FramelessWindowHint); //窗体没有面板边框和标题栏
    setWindowOpacity(0.5);  //半透明
    QTimer* timer = new QTimer(this); //定时器对象、
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));

    timer->start(500);
    showTime();  //初始化时间显示
    resize(150, 60);
    showColon = true;

}

void DigiClock::showTime() //冒号在闪烁
{
    QTime time = QTime::currentTime();  //time保存在一个QTime类的对象中
    QString text = time.toString("hh:mm"); //对象转字符串
    if(showColon){
        text[2] = ':';
        showColon = false;
    }
    else {
        text[2] = ' ';
        showColon = true;
    }
    display(text);
}

void DigiClock::mousePressEvent(QMouseEvent *event){
    if (event->button()==Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();  //????
    }

    if (event->button() == Qt::RightButton)
    {
        close();
    }
}

void DigiClock::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}
