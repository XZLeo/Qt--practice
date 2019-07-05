#include "dialog.h"
#include <QFileDialog>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("各种标准对话框的实例"));
    //添加标准文件对话框实例
    fileBtn = new QPushButton;
    fileBtn->setText(tr("文件标准对话框实例"));
    fileLineEdit = new QLineEdit;

    //布局管理
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(fileBtn, 0, 0); //布局管理 pushbutton和lineedit的位置
    mainLayout ->addWidget(fileLineEdit, 0, 1);

    //连接信号与槽
    connect(fileBtn, SIGNAL(clicked()), this, SLOT(showFile()));  //完全用代码写，不直观也不便于平面设计！！

    //添加标准颜色对话框实例的内容
    colorBtn = new QPushButton;
    colorBtn->setText(tr("标准颜色对话框实例"));
    colorFrame = new QFrame;
    colorFrame->setFrameShape(QFrame::Box);
    colorFrame->setAutoFillBackground(true);

    mainLayout->addWidget(colorBtn, 1, 0);
    mainLayout->addWidget(colorFrame, 1, 1);

    connect(colorBtn, SIGNAL(clicked()), this, SLOT(showColor())); //SLOT

    //标准输入对话框，只有这个是在inputdlg.cpp中自己写的子窗口，前两个都是调用QFile和QColor类的内置函数就能实现点击后打开的打开对话框
    inputBtn = new QPushButton;
    inputBtn->setText(tr("标准输入对话框实例"));

    mainLayout->addWidget(inputBtn, 3, 0);
    connect(inputBtn, SIGNAL(clicked()), this, SLOT(showInputDlg()));//点击input按钮，显示输入对话框

}

Dialog::~Dialog()
{

}

void Dialog::showFile()
{

    QString s = QFileDialog::getOpenFileName(this, "open file dialog", "/", "c++ files(*.cpp);; C files(*.c);;Head files(*.h)");
    fileLineEdit->setText(s);
}

void Dialog::showColor(){
    QColor c = QColorDialog::getColor(Qt::blue); //点击cilcked是信号，触发槽函数showColor，showcolor的重点是getColor
    if(c.isValid()){
        colorFrame->setPalette(QPalette(c));
    }

}

void Dialog::showInputDlg()
{
    inputDlg = new InputDlg(this); //用于显示对话框
    inputDlg->show();
}
