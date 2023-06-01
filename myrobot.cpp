
#include "myrobot.h"
#include "ui_myrobot.h"

#include "ui_myrobot.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QLCDNumber>

MyRobot::MyRobot(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyRobot)
{
    ui->setupUi(this);

    ui->crcNum->overflow(&MyRobot::crcAffichage);

    connect(ui->connect,&QPushButton::clicked,this,&MyRobot::connection);
    connect(ui->disconnect,&QPushButton::clicked,this,&MyRobot::deconnection);
    connect(ui->haut,&QPushButton::clicked,this,&MyRobot::haut);
    connect(ui->bas,&QPushButton::clicked,this,&MyRobot::bas);
    connect(ui->gauche,&QPushButton::clicked,this,&MyRobot::gauche);
    connect(ui->droite,&QPushButton::clicked,this,&MyRobot::droite);
}

MyRobot::~MyRobot()
{
    delete ui;
}

void MyRobot::crcAffichage(){
    short int crc = WifiBot.crcReturn();
    ui->crcNum->display(crc);
}

void MyRobot::connection(){
    WifiBot.doConnect();
}

void MyRobot::deconnection(){
    WifiBot.disConnect();
}

void MyRobot::haut(){
    WifiBot.avancer();
}

void MyRobot::bas(){
    WifiBot.reculer();
}

void MyRobot::gauche(){
    WifiBot.gauche();
}

void MyRobot::droite(){
    WifiBot.droite();
}

//Contrôle du robot et de la caméra avec les différentes touche du clavier
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
}

