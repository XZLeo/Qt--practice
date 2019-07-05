#ifndef PALETTE_H
#define PALETTE_H

#include <QDialog>

#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>

class Palette : public QDialog
{
    Q_OBJECT

public:
    Palette(QWidget *parent = 0);
    ~Palette();
    void createCtrlFrame(); //窗体左半侧颜色选择区
    void createContentFrame(); //窗体右半部分
    void fillColorList(QComboBox* ); //向下拉列表框中插入不同的颜色选项

private slots:
    void showWindow();
    void showWindowText();
    void showButton();
    void showButtonText();
    void showBase();
private:
    QFrame* ctrlFrame; //颜色选择面板
    QLabel* windowLabel;
    QComboBox* windowComboBox; //下拉选择框
    QLabel* windowTextLabel;
    QComboBox* windowTextComboBox;
    QLabel* buttonLabel;
    QComboBox* buttonComboBox;
    QLabel* buttonTextLabel;
    QComboBox* buttonTextComboBox;
    QLabel* baseLabel;
    QComboBox* baseComboBox;
    QFrame* contentFrame;
    QLabel* label1;
    QComboBox* comboBox1;
    QLabel* label2;
    QLineEdit* lineEdit2;
    QTextEdit* textEdit;
    QPushButton* OkBtn;
    QPushButton* CancelBtn;
};

#endif // PALETTE_H
