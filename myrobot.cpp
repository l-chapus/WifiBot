#include "myrobot.h"

#include "ui_myrobot.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <iostream>

MyRobot::MyRobot(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyRobot)
{
    ui->setupUi(this);

    connect(ui->connect,&QPushButton::clicked,this,&MyRobot::connection);
    connect(ui->disconnect,&QPushButton::clicked,this,&MyRobot::deconnection);
    connect(ui->droit,&QPushButton::clicked,this,&MyRobot::droit);
    connect(ui->gauche,&QPushButton::clicked,this,&MyRobot::gauche);
    connect(ui->haut,&QPushButton::clicked,this,&MyRobot::avancer);
    connect(ui->bas,&QPushButton::clicked,this,&MyRobot::reculer);
}

MyRobot::~MyRobot()
{
    delete ui;
}

void MyRobot::connection(){
    WifiBot.doConnect();
}
void MyRobot::deconnection(){
    WifiBot.disConnect();
}

void MyRobot::droit(){
    WifiBot.droite();
}
void MyRobot::gauche(){
    WifiBot.gauche();
}
void MyRobot::avancer(){
    WifiBot.avancer();
}
void MyRobot::reculer(){
    WifiBot.reculer();
}

//Contrôle du robot avec les différentes touche du clavier
void MyRobot::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z)
    {
        WifiBot.avancer();
    }
    if (event->key() == Qt::Key_Q)
    {
        WifiBot.gauche();
    }
    if (event->key() == Qt::Key_S)
    {
        WifiBot.reculer();
    }
    if (event->key() == Qt::Key_D)
    {
        WifiBot.droite();
    }
    if (event->key() == Qt::Key_Space)
    {
        WifiBot.stop();
    }
}
