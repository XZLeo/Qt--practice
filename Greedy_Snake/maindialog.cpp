#include "maindialog.h"
#include <QPushButton>
#include <unistd.h>
#include <QTextEdit>
#include <QSpacerItem>



maindialog::maindialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Greedy Snake Game");
    //设置背景颜色
    this->setAutoFillBackground(true);
    QPalette p = this->palette();
    p.setColor(QPalette::Window, Qt::lightGray);
    setWindowOpacity(0.9);
    this->setPalette(p);


    //用于显示右侧按钮,里面要设置画面和布局
    gameWidget = new game;
    gameWidget->grabKeyboard();  //由内层窗口接收所有键盘事件，外面的不响应
    createMenu();
    //设置mainLayout
    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->setMargin(30);
    mainLayout->setSpacing(30);
    mainLayout->addWidget(gameWidget, 0, 0, 1, 2);
    mainLayout->addLayout(rightLyot, 0, 2);

    resize(600, 450);
    sleep(5);
}

maindialog::~maindialog()
{

}

void maindialog::createMenu()
{

   scoreLabel = new QLabel(tr("Your Score: "));
   //分数应该实时显示
   startBtn = new QPushButton("Start Game", this);
   scoreLine = new QLabel("000", this);
   update();
   pauseBtn = new QPushButton("Pause Game", this);
   endBtn = new QPushButton("End Game", this);

   //QSpacerItem upBlk = new QSpacerItem();

   rightLyot = new QGridLayout();
   //rightLayout
   rightLyot->addWidget(scoreLabel, 1, 0,1, 1);
   rightLyot->addWidget(scoreLine, 1, 1, 1, 1);
   rightLyot->addWidget(startBtn, 2, 0, 1, 2); //1 row 2 column
   rightLyot->addWidget(pauseBtn, 3, 0, 1, 2);
   rightLyot->addWidget(endBtn, 4, 0, 1, 2);
   /*
   rightLyot->setRowStretch(0, 1);
   rightLyot->setRowStretch(1, 2);
   rightLyot->setRowStretch(2, 2);
   rightLyot->setRowStretch(3, 2);*/

   //slot   
   connect(startBtn, SIGNAL(clicked()), gameWidget, SLOT(start()));  //public slot的调用不需要写成gameWidget->start()
   connect(pauseBtn, SIGNAL(clicked()), gameWidget, SLOT(stop()));
   connect(endBtn, SIGNAL(clicked()), gameWidget, SLOT(clear()));
   connect(gameWidget, SIGNAL(death()), gameWidget, SLOT(showInformationMsg())); //弹出对话框
   connect(gameWidget, SIGNAL(lenChg()), this, SLOT(setScore()));
}

void maindialog::setScore()
{
    scoreLine->setNum(gameWidget->getScore());
}



