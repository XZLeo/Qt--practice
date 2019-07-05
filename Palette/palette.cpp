#include "palette.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>

Palette::Palette(QWidget *parent)
    : QDialog(parent)
{
    createCtrlFrame(); //成员函数，创建颜色选区
    createContentFrame(); //成员函数
    QHBoxLayout* mainLayout = new QHBoxLayout(this); //为什么要this？
    mainLayout->addWidget(ctrlFrame);
    mainLayout->addWidget(contentFrame);
}

Palette::~Palette()
{

}

void Palette::createCtrlFrame()
//创建颜色选区
{
    ctrlFrame = new QFrame; //颜色选择面板
    windowLabel = new QLabel(tr("QPalette::Window: ")); //初始化
    windowComboBox = new QComboBox;
    fillColorList(windowComboBox); //成员函数，向下拉列表框中插入不同的颜色选项
    connect(windowComboBox, SIGNAL(activated(int)), this, SLOT(showWindow())); //下拉表框的activated信号， 改变背景色的槽函数

    windowTextLabel = new QLabel(tr("QPalette::WindowText: "));
    windowTextComboBox = new QComboBox;
    fillColorList(windowTextComboBox);
    connect(windowTextComboBox, SIGNAL(activated(int)), this, SLOT(showWindowText()));

    buttonLabel = new QLabel(tr("QPalette::Button: "));
    buttonComboBox = new QComboBox;
    fillColorList(buttonComboBox);
    connect(buttonComboBox, SIGNAL(activated(int)), this, SLOT(showButton()));

    buttonTextLabel = new QLabel(tr("QPalette::buttonText: "));
    buttonTextComboBox = new QComboBox;
    fillColorList(buttonTextComboBox);
    connect(buttonTextComboBox, SIGNAL(activated(int)), this, SLOT(showButtonText()));

    baseLabel =new QLabel(tr("QPalette::Base: "));
    baseComboBox = new QComboBox;
    fillColorList(baseComboBox);
    connect(baseComboBox, SIGNAL(activated(int)), this, SLOT(showBase()));

    QGridLayout* mainLayout = new QGridLayout(ctrlFrame);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(windowLabel, 0, 0);
    mainLayout->addWidget(windowComboBox, 0, 1);
    mainLayout->addWidget(windowTextLabel, 1, 0);
    mainLayout->addWidget(windowTextComboBox, 1, 1);
    mainLayout->addWidget(buttonLabel, 2, 0);
    mainLayout->addWidget(buttonComboBox, 2, 1);
    mainLayout->addWidget(buttonTextLabel, 3, 0);
    mainLayout->addWidget(buttonTextComboBox, 3, 1);
    mainLayout->addWidget(baseLabel, 4, 0);
    mainLayout->addWidget(baseComboBox, 4, 1);
}


void Palette::createContentFrame()  //用于展示各种被改变的颜色区域
{
    contentFrame =new QFrame;

    label1 = new QLabel(tr("请选择一个值："));
    comboBox1 = new QComboBox;
    label2 = new QLabel(tr("请输入字符串："));
    lineEdit2 = new QLineEdit;
    textEdit = new QTextEdit;

    QGridLayout* TopLayout = new QGridLayout;
    TopLayout->addWidget(label1, 0, 0);
    TopLayout->addWidget(comboBox1, 0, 1);
    TopLayout->addWidget(label2, 1, 0);
    TopLayout->addWidget(lineEdit2, 1, 1);
    TopLayout->addWidget(textEdit, 2, 0, 1, 2); //2个参数都是占单独的一个cell，4个参数是起始网格坐标、占行数、列数

    OkBtn = new QPushButton(tr("确认"));
    CancelBtn = new QPushButton(tr("取消"));
    QHBoxLayout* BottomLayout = new QHBoxLayout; //横向排列
    BottomLayout->addStretch(1);  //使按钮居右
    BottomLayout->addWidget(OkBtn);
    BottomLayout->addWidget(CancelBtn);
    //上面两种布局放一起
    QVBoxLayout* mainLayout = new QVBoxLayout(contentFrame);  //由contentFrame生成的总布局
    mainLayout->addLayout(TopLayout);
    mainLayout->addLayout(BottomLayout);
}

void Palette::showWindow()
//响应对背景颜色的选择，槽函数SLOT,整个palette类就这个函数最有用，后面几个函数只是颜色主题的不同
{
    QStringList colorList = QColor::colorNames(); //获得当前选择的颜色值
    QColor color = QColor(colorList[windowComboBox->currentIndex()]); //从下拉菜单获取index，得到colorlist中对应的颜色
    contentFrame->setAutoFillBackground(true);
    QPalette p = contentFrame->palette(); //获取contentFrame的调色板信息
    p.setColor(QPalette::Window, color); //第一个参数为颜色主题，window类颜色即背景色
    contentFrame->setPalette(p);
    contentFrame->update();
}

void Palette::showWindowText()
{
    QStringList colorList = QColor::colorNames();
    QColor color = colorList[windowTextComboBox->currentIndex()];
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::WindowText, color); //only this sentence matters!
    contentFrame->setPalette(p);
    contentFrame->update();
}

void Palette::showButton()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[buttonComboBox->currentIndex()]);
    contentFrame->setAutoFillBackground(true); //书中没加！！！！！！！！！
    qDebug()<<color;
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Button, color);
    contentFrame->setPalette(p);
    contentFrame->update();
}

void Palette::showButtonText()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[buttonTextComboBox->currentIndex()]);
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::ButtonText, color);
    contentFrame->setPalette(p);
    contentFrame->update();
}

void Palette::showBase() //右侧中间一大块的颜色
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[baseComboBox->currentIndex()]);

    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Base, color);
    contentFrame->setPalette(p);
    contentFrame->update();
}

//去看help里的colorRole就知道这些window了，除此之外还有很多别的可以设计
//实际使用中会用setcolor这几句设置颜色就行了

void Palette::fillColorList(QComboBox *comboBox)
{
    QStringList colorList = QColor::colorNames();
    QString color;
    foreach(color, colorList)
    {
        QPixmap pix(QSize(70, 20)); //新建QPix对象作为显示颜色的图标
        pix.fill(QColor(color));
        comboBox->addItem(QIcon(pix), NULL); //addItem函数为下拉列表框插入一个条目
        comboBox->setIconSize(QSize(70, 20));
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}

































