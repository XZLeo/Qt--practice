#include "keyevent.h"
#include <QPainter>
#include <QDebug>
#include <QImageReader>

keyevent::keyevent(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(tr("键盘事件"));
    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);
    setPalette(palette);
    setMaximumSize(512, 256);
    setMinimumSize(512, 256);
    //初始化各private成员变量
    width = size().width();
    height = size().height();
    pix = new QPixmap(width, height);
    pix->fill(Qt::white);

    //int a = 1;
    //qDebug()<<a; //输出信息用于调试
    //qDebug() << "Supported formats:" << QImageReader::supportedImageFormats();
    //显示支持png格式
    /*qDebug()<<*/image.load("/home/leo/Qt/keyevent/image/glass.png");//返回值为true,说明是load成功的
    //要用绝对路径，不然无法加载图片
    startX = 100;
    startY = 100;
    step = 20;

    drawPix(); //此处调用成员函数，画出网格
    resize(512, 256);

}

keyevent::~keyevent()
{
    //delete ui;
}
//函数的功能我似乎高懂了，但是在哪里被调用的？
void keyevent::drawPix()
//在QPixmap上画图像
{
    pix->fill(Qt::white); //refresh pix的底色为白色
    QPainter* painter = new QPainter;
    QPen pen(Qt::DotLine); //设置画笔的线性
    for (int i=step; i<width; i=i+step)
        //绘制纵向网格
        {
            painter->begin(pix); //制定pix为绘图设备
            painter->setPen(pen);
            painter->drawLine(QPoint(i, 0),QPoint(i, height)); //线的横坐标都是i，纵坐标是0-height
            painter->end();
    }

    for (int j=step; j<height; j=j+step)
        //绘制纵向网格
        {
            painter->begin(pix); //指定pix为绘图设备
            painter->setPen(pen);
            painter->drawLine(QPoint(0, j),QPoint(width, j)); //线的横坐标都是i，纵坐标是0-height
            painter->end();
    }

    painter->begin(pix);
    painter->drawImage(QPoint(startX, startY), image); //画中间的小图标
    painter->end();
}

void keyevent::keyPressEvent(QKeyEvent *event){
    if (event->modifiers() == Qt::ControlModifier)
    //按下了ctrl键的事件处理（细微移动）
    {
        if (event->key() == Qt::Key_Left) //各种key的事件
            startX = (startX - 1<0)?startX:startX-1; //三目运算符
        //这句的意思：如果按下左键，若现在图标的位置没超过左界，就向左移动一格

        if (event->key() == Qt::Key_Right)
            startX = (startX + 1 + image.width() > width)?startX:startX+1;
        if (event->key() == Qt::Key_Up)
            startY = (startY - 1<0)?startY:startY-1;
        if (event->key() == Qt::Key_Down)
            startY = (startY + 1 + image.height()>height)?startY:startY+1;
    }
    else{//没按ctrl，步进制为网格步长
        startX = startX - startX%step; //将图标起始位置调整到网格的格点上去
        startY = startY - startY%step;
        if (event->key() == Qt::Key_Left)
            startX = (startX - step<0)?startX:startX-step;

        if (event->key() == Qt::Key_Right)
            startX = (startX + step + image.width() > width)?startX:startX+step;
        if (event->key() == Qt::Key_Up)
            startY = (startY - step<0)?startY:startY-step;
        if (event->key() == Qt::Key_Down)
            startY = (startY + step + image.height()>height)?startY:startY+step;
        if (event->key() == Qt::Key_0){
            //按下home键，图标回到原点
            startX = 0;
            startY = 0;
        }
        if (event->key() == Qt::Key_1){
            startX = width - image.width();
            startY = height - image.height();
        }
    }
    drawPix();
    update();
}

void keyevent::paintEvent(QPaintEvent *){
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(QPoint(0, 0), *pix);
    painter.end();
}
