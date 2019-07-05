#include "mainwindow.h"
#include <QTextEdit>
#include <unistd.h> //linux系统使用sleep

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Splash Example");
    QTextEdit* edit = new QTextEdit;
    edit->setText("SPlash Example!");
    setCentralWidget(edit);
    resize(600, 450);
    sleep(30); //休眠10秒 usleep 微妙级
}

MainWindow::~MainWindow()
{

}
