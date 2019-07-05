#ifndef DIGICLOCK_H
#define DIGICLOCK_H
#include <QLCDNumber>


class DigiClock : public QLCDNumber
{
    Q_OBJECT
public:
    DigiClock(QWidget* parent=0);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);

signals:

public slots:
    void showTime(); //显示当前时间

private:
    QPoint dragPosition; //保存鼠标相对电子时钟窗体左上角的偏移值
    bool showColon;
};

#endif // DIGICLOCK_H
