#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QLabel>
#include "game.h"
#include <QPushButton>
#include <QGridLayout>

class maindialog : public QDialog
{
    Q_OBJECT

public:
    maindialog(QWidget *parent = 0);
    ~maindialog();
    void createMenu();
public slots:
    void setScore();

private:

    QGridLayout* rightLyot;
    game* gameWidget;
    QLabel* scoreLabel;
    QLabel* scoreLine;
    QPushButton* startBtn;  //暂时不开发存档功能
    QPushButton* pauseBtn;
    QPushButton* endBtn;
};

#endif // MAINDIALOG_H
