#ifndef MYROBOT_H
#define MYROBOT_H

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class MyRobot; }
QT_END_NAMESPACE

class MyRobot : public QMainWindow

{
    Q_OBJECT

public:
    MyRobot(QWidget *parent = nullptr);
    ~MyRobot();

private:
    Ui::MyRobot *ui;
};

#endif // MYROBOT_H
