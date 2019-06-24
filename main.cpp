#include "keyevent.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    keyevent w; //调用构造函数
    w.show(); //可能在这句话里会到用各种函数

    return a.exec();
}
