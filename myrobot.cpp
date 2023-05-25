
#include "myrobot.h"
#include "ui_myrobot.h"

#include "ui_myrobot.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>

MyRobot::MyRobot(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyRobot)
{
    ui->setupUi(this);

    connect(ui->connect,&QPushButton::clicked,this,&MyRobot::connection);
}

MyRobot::~MyRobot()
{
    delete ui;
}

void MyRobot::connection(){
    WifiBot.doConnect();
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

