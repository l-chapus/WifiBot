#include "myrobot.h"

#include "ui_Robot.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

MyRobot::MyRobot(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyRobot)
{
    ui->setupUi(this);


}

MyRobot::~MyRobot()
{
    delete ui;
}
