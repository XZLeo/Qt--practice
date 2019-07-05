#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QPainter>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap;
    pixmap.load("E:/Qt/SplashScreen/glass.png");//加载不了图片????

    QSplashScreen splash(pixmap); //使用pixmap创建一个QSplashscreen对象
    splash.show();
    a.processEvents(); //程序显示启动画面时仍能响应鼠标等其他事件；


    MainWindow w; //主函数中show的都是另一个.cpp中创建的类的对象；
    w.show();
    splash.finish(&w);//&w表示主窗体对象完成初始化后，结束启动画面

    return a.exec();
}
