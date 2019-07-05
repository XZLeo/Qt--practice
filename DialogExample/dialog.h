#ifndef DIALOG_H
#define DIALOG_H


#include <QLineEdit>
#include <QGridLayout>   //主管布局
#include <QPushButton>
//各种dialog的库文件
#include <QDialog>
#include <QColorDialog>
#include "inputdlg.h"

class Dialog : public QDialog //Dialog类和InputDlg类的都是公共继承QDialog，其中InputDlg类是Dialog类的私有成员
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
private:
    QPushButton *fileBtn;
    QLineEdit *fileLineEdit;
    QGridLayout *mainLayout;
    QPushButton *colorBtn;
    QFrame *colorFrame;
    QPushButton* inputBtn;
    InputDlg* inputDlg; //添加为一个成员

private slots:
    void showFile();
    void showColor();
    void showInputDlg();

};

#endif // DIALOG_H
