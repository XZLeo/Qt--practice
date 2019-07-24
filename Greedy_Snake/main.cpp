#include "maindialog.h"
#include <QApplication>

#include <QSplashScreen>
#include <QPainter>
#include <QPixmap>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap;
    pixmap.load("F:/QtWorkSpace/GreedySnake/icon.png"); //开机画面
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();

    maindialog w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
