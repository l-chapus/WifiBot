#include "myrobot.h"

#include "ui_myrobot.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QWebEngineView>
#include <QWidget>
#include <iostream>

MyRobot::MyRobot(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyRobot)
{
    ui->setupUi(this);

    // gestion de connxion du robot
    connect(ui->connect,&QPushButton::clicked,this,&MyRobot::connection);
    connect(ui->disconnect,&QPushButton::clicked,this,&MyRobot::deconnection);

    //mouvement du robot
    connect(ui->droit,&QPushButton::pressed,this,&MyRobot::droit);
    connect(ui->droit,&QPushButton::released,this,&MyRobot::stop);
    connect(ui->gauche,&QPushButton::pressed,this,&MyRobot::gauche);
    connect(ui->gauche,&QPushButton::released,this,&MyRobot::stop);
    connect(ui->haut,&QPushButton::pressed,this,&MyRobot::avancer);
    connect(ui->haut,&QPushButton::released,this,&MyRobot::stop);
    connect(ui->bas,&QPushButton::pressed,this,&MyRobot::reculer);
    connect(ui->bas,&QPushButton::released,this,&MyRobot::stop);

    // affichage de la caméra
    QWebEngineView *video = new QWebEngineView();
    afficherCamera(video);
}

MyRobot::~MyRobot()
{
    delete ui;
}

// bouton de connexion
void MyRobot::connection(){
    WifiBot.doConnect();
}

// bouton de déconnexion
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
void MyRobot::stop(){
    WifiBot.stop();
}

//Contrôle le déplacement du robot avec les différentes touche du clavier
void MyRobot::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z)
    {
        WifiBot.avancer();
    }
    else if (event->key() == Qt::Key_Q)
    {
        WifiBot.gauche();
    }
    else if (event->key() == Qt::Key_S)
    {
        WifiBot.reculer();
    }
    else if (event->key() == Qt::Key_D)
    {
        WifiBot.droite();
    }
    else
    //if (event->key() == Qt::Key_Space)
    {
        WifiBot.stop();
    }
}

void MyRobot::afficherCamera(QWebEngineView *video){
    video -> setGeometry(0,0,451,481);
    QUrl url = QUrl("https://192.168.1.106:8080/?action=stream");

    //QUrl url = QUrl("https://192.168.10.1:8080/?action=stream");
    video->load(url);
    video->setParent(ui->cam);
    video->show();
}
