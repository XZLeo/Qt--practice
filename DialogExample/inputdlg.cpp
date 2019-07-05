#include "inputdlg.h"
#include <QInputDialog>


InputDlg::InputDlg(QWidget* parent):QDialog(parent)
{
    setWindowTitle(tr("标准输入对话框实例"));
    //name
    nameLabel1 = new QLabel;
    nameLabel1->setText(tr("姓名："));
    nameLabel2 = new QLabel;
    nameLabel2->setText(tr("周和军"));
    nameLabel2->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    nameBtn = new QPushButton;
    nameBtn->setText(tr("change name"));
    //gender
    sexLabel1 = new QLabel;
    sexLabel1->setText(tr("性别"));
    sexLabel2 = new QLabel;
    sexLabel2->setText(tr("male"));
    sexLabel2->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    sexBtn = new QPushButton;
    sexBtn->setText(tr("修改性别"));
    //age
    ageLabel1=new QLabel;
    ageLabel1->setText(tr("修改年龄"));
    ageLabel2=new QLabel;
    ageLabel2->setText(tr("21"));
    ageLabel2->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    ageBtn = new QPushButton;
    ageBtn->setText(tr("change age"));
    //score
    scoreLabel1=new QLabel;
    scoreLabel1->setText(tr("grade"));
    scoreLabel2=new QLabel;
    scoreLabel2->setText(tr("80"));
    scoreLabel2->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    scoreBtn = new QPushButton;
    scoreBtn->setText(tr("change grade"));
    scoreBtn = new QPushButton;
    scoreBtn->setText(tr("修改grade"));
    //layout
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(nameLabel1, 0, 0);
    mainLayout->addWidget(nameLabel2, 0, 1);
    mainLayout->addWidget(nameBtn, 0, 2);
    mainLayout->addWidget(sexLabel1, 1, 0);
    mainLayout->addWidget(sexLabel2, 1, 1);
    mainLayout->addWidget(sexBtn, 1, 2);
    mainLayout->addWidget(ageLabel1, 2, 0);
    mainLayout->addWidget(ageLabel2, 2, 1);
    mainLayout->addWidget(ageBtn, 2, 2);
    mainLayout->addWidget(scoreLabel1, 3, 0);
    mainLayout->addWidget(scoreLabel2, 3, 1);
    mainLayout->addWidget(scoreBtn, 3, 2);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    //slot
    connect(nameBtn, SIGNAL(clicked()),this,SLOT(ChangeName())); //信号和槽都是函数，所以都得带括号！ //一共三层对话框
    connect(sexBtn, SIGNAL(clicked()),this,SLOT(ChangeSex()));
    connect(ageBtn, SIGNAL(clicked()),this,SLOT(ChangeAge()));
    connect(scoreBtn, SIGNAL(clicked()),this,SLOT(ChangeScore()));

    }

void InputDlg::ChangeName() //标准字符串输入对话框
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("标准字符串输入对话框"),
                                         tr("please input name:"), QLineEdit::Normal, nameLabel2->text(), &ok);
    if (ok && !text.isEmpty())//用户点击了 确认，而且输入不为空
        nameLabel2->setText(text);
}

void InputDlg::ChangeSex() //标准条目选择对话框
{
    QStringList SexItmes;
    SexItmes << tr("男")<<tr("女");
    bool ok;
    QString SexItem = QInputDialog::getItem(this, tr("标准条目选择对话框"), tr("请选择性别"),
                                            SexItmes, 0, false, &ok);
    if (ok && !SexItem.isEmpty())
        sexLabel2->setText(SexItem);
}

void InputDlg::ChangeAge()//标准int类型输入对话框
{

}

void InputDlg::ChangeScore() //标准double类型输入对话框
{

}
