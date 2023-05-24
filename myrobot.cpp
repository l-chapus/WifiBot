
#include "myrobot.h"
#include "ui_myrobot.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

MyRobot::MyRobot(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyRobot)
{
    ui->setupUi(this);

    ui->crcNum->display(23);

}

MyRobot::~MyRobot()
{
    delete ui;
}



