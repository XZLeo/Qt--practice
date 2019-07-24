#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>

class game : public QWidget
{
    Q_OBJECT
public:

    explicit game(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*); //将pix画到窗口gameWidget上
    int getScore();
    void getPos();  //根据oldDirec和direc计算下次位置
    void keyPressEvent(QKeyEvent*);
    void drawPix();

signals:
    void death();
    void lenChg();

public slots:
    void clear();  //对应mainWindow的end按钮
    void stop();  //对用pause按钮,一下暂停，再按一下开始
    void start();
    void drawSnk();
    void drawFood(); //在pix上画食物，避免和蛇身重叠
    void showInformationMsg();

private:
    //蛇的属性
    int bodyLth;  //记录蛇身长度,私有成员是不能直接被别的类访问的，只有通过公有接口函数
    int bodyPos[100][2]; //记录蛇身的每一个方块位置，最大长100,都存左上角坐标，x,y
    int nxPos[100][2];
    //蛇的运动属性
    int startPos[2]; //第一次蛇头的位置
    int direc;
    int oldDirec;
    //画布的属性
    int width;
    int height;
    int step;

    //时钟
    QTimer* timer;

    QPixmap* pix; //绘图设备，放在gameWidget上
    //食物的属性
    int foodX;
    int foodY;
    //QTextEdit* edit;
    //标志位
    bool stopFlag;
    bool foundFlag;
};

#endif // GAME_H
