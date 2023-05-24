#ifndef MYROBOT_H
#define MYROBOT_H

#include <QMainWindow>
#include "Robot.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MyRobot; }
QT_END_NAMESPACE

class MyRobot : public QMainWindow

{
    Q_OBJECT

public:
    MyRobot(QWidget *parent = nullptr);
    ~MyRobot();
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MyRobot *ui;
    Robot WifiBot;
};

#endif // MYROBOT_H
