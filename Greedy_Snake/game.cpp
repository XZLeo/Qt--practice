#include "game.h"
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <QPen>
#include "windows.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QDebug>
#include <QGridLayout>

game::game(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);
    QPalette p = this->palette();
    p.setColor(QPalette::Window, Qt::gray);
    this->setPalette(p);

    //widget size
    this->setMaximumSize(500, 500);
    this->setMinimumSize(500, 500);

    //pix画布属性，画背景网格,方格划分成20*20
    width = size().width();
    height = size().height();
    step = width/25;
    pix = new QPixmap(width, height);
    pix->fill(Qt::white);
    resize(500, 500);

    //初始化标志位
    stopFlag = false;
    foundFlag = true;
    //Timer, draw the snake
    timer = new QTimer(this);
   //每个0.5s更新一次画面  timer放到start里面就能保证按start才开始游戏，并且每次都会重新初始化


    drawPix();
    connect(timer, SIGNAL(timeout()), this, SLOT(drawFood()));//画食物，被找到后更新食物位置
    connect(timer, SIGNAL(timeout()), this, SLOT(drawSnk())); //先调用drawfood，后drawSnk会导致吃到食物那step没有食物产生，有等到下一次
}


int game::getScore() //没有调用也会自动打印？
{
    //mainwindow中显示bodyLth用
    return bodyLth;
}

void game::start(){
    //initialize the snake
    bodyLth = 1;
    QRandomGenerator gen;
    bodyPos[0][0] = gen.bounded(20)*step;
    bodyPos[0][1] = gen.bounded(20)*step;
    nxPos[0][0] = bodyPos[0][0];
    nxPos[0][1] = bodyPos[0][1];  //这样写的问题是按了start才会开始游戏
    direc = 1;//固定每次蛇的初始方向都是朝上
    oldDirec = direc;
    timer->start(300);
}

void game::stop(){ //按一下暂停，按两下开始
    if (!stopFlag){  //!是 非， ~是按位取反
        qDebug()<<"out";
        timer->stop();
        stopFlag = true;
    }
    else {
        qDebug()<<"in";
        timer->start(300);
        stopFlag = false;
    }

}

void game::clear()  //点击之后方块消失，再开始按start重新开始
{
    qDebug()<<"clear";
    //清空关于蛇的属性
    bodyLth = 0;
    for(int i=0; i<100; i++)
        for (int j = 0; j< 2; j++)
            bodyPos[i][j] = 0;
    //清空画面
    drawPix();
    update();
    timer->stop();
}


void game::drawPix()
{
    //只用来画背景网格
    pix->fill(Qt::cyan);
    QPainter* painter = new QPainter;
    QPen pen(Qt::white, 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    pen.setWidth(2); //用构造函数的麻烦在于要记住每种argument的顺序
    pen.setStyle((Qt::PenStyle)1);
    for(int i=step; i<width; i=i+step)
    {
        painter->begin(pix);
        painter->setPen(pen);
        painter->drawLine(QPoint(i, 0), QPoint(i, height));
        painter->end();
    }

    for(int j=step; j<height; j=j+step)
    {
        painter->begin(pix);
        painter->setPen(pen);
        painter->drawLine(QPoint(0, j), QPoint(width, j));
        painter->end();
    }
}

void game::drawFood()  //找到了再画新的
{
   drawPix();
   QRandomGenerator qrnd;
   qrnd.seed(static_cast<quint32>(QTime::currentTime().second()));  //因为用的是秒做seed，所以当Timer（500）半秒的时候，每两次产生的随机数是一样的
   //找到了食物，则重新产生一个位置
   if (foundFlag)
   {
       foodX = qrnd.bounded(20)*step;
       foodY = qrnd.bounded(20)*step;
       foundFlag = false;
   }

   //draw the food rectangle
   QPainter* painter = new QPainter;
   QPen pen(Qt::yellow, 8);
   painter->begin(pix);
   painter->setPen(pen);
   painter->drawRect(foodX, foodY, step, step);
   painter->end();
   update();
}

void game::getPos()  //根据direct计算下一步蛇头的位置
{
    int x=0;
    int y=0;
    if (direc == 1)
    {
        x = 0;
        y = -1;
    }
    if (direc == 4)
    {
        x = 0;
        y = 1;
    }
    if (direc == 2)
    {
        x = -1;
        y = 0;
    }
    if (direc == 3)
    {
        x = 1;
        y = 0;
    }

    nxPos[0][0] = bodyPos[0][0] + x*step;
    nxPos[0][1] = bodyPos[0][1] + y*step;
    //检测是否死亡
    if (nxPos[0][0] <0 or nxPos[0][0]>480 or nxPos[0][1]<0 or nxPos[0][1]>480)
    {
        emit death();
    }

    if (nxPos[0][0] != foodX or nxPos[0][1] != foodY ) //不会撞food
    {

    }
    else {  //撞food，整体不动，头起多了一节
        bodyLth++;
        foundFlag = true;  //更新食物的位置
        emit lenChg();
    }
    for (int i=1; i<bodyLth; i++)
    {
        nxPos[i][0] = bodyPos[i-1][0];
        nxPos[i][1] = bodyPos[i-1][1];
    }
    //避免成环
    for (int i=0; i<bodyLth; i++)
    {
        bodyPos[i][0] = nxPos[i][0];
        bodyPos[i][1] = nxPos[i][1];

        if (i != 0 && bodyPos[0][0] == bodyPos[i][0] && bodyPos[0][1] == bodyPos[i][1])
            emit death();
    }
}

void game::keyPressEvent(QKeyEvent *event)  //如果在1s内按键按的太频繁，是会按先后顺序累加的
{
    int key = 0;
    if (event->key() == Qt::Key_Up)
        key = 1;
    else if (event->key() == Qt::Key_Down)
        key = 4;
    else if (event->key() == Qt::Key_Left)
        key = 2;
    else if (event->key() == Qt::Key_Right)
        key = 3;
    else
        key = 1000;
   //只用于改变direc，
    if (key != 5 - direc and key != 1000 and !stopFlag)
    {
        //只要按的是方向键，且不是反向的
        direc = key;
    }//否则不改变direc
}

void game::drawSnk()
{
    getPos(); //还能防止1s按很多次键
    //只需要蛇的位置参数就能画出来
    QPainter* painter = new QPainter;
    QPen pen(Qt::green, 8);
    for (int i=0; i<bodyLth; i++)
    {
        painter->begin(pix);
        painter->setPen(pen);
        painter->drawRect(bodyPos[i][0], bodyPos[i][1],
                step, step);
        painter->end();
    }
    update();
}

void game::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this); //this应该是当前窗口gameWidget
    painter.drawPixmap(QPoint(0, 0), *pix);
    painter.end();
}

void game::showInformationMsg()
{
    QMessageBox::information(this, tr("消息框"), tr("You have losed the game."));
    clear();  //因为这个调用，导致蛇成环的时候不是画面停止，而是直接被清除
}

//目前的问题包括：食物可能产生在蛇身上，那样表现为此刻没有食物，因为先画的食物，再画蛇会覆盖掉，
//但这样会造成玩家一段时间内看不到食物在哪，蛇头撞不到食物，则一直不会出现新的食物，直到蛇身移开才会重新看到


//加入调速功能
