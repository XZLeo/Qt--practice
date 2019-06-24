#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <QMainWindow>

#include <QWidget>
#include <QKeyEvent>
#include <QPaintEvent>


class keyevent : public QWidget
{
    Q_OBJECT

public:
    explicit keyevent(QWidget *parent = nullptr); //构造函数
    ~keyevent();
    void drawPix();
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);

private:
    QPixmap* pix; //作为绘图设备
    QImage image; //图中间的小图标
    int startX;
    int startY;
    int width;
    int height;
    int step; //网格大小，移动的步进制
};

//键盘事件不同于前面用了pushbutton的点击出发槽函数，里面没有用到slot
#endif // KEYEVENT_H
