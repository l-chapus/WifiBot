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
    connect(ui->droite,&QPushButton::pressed,this,&MyRobot::droit);
    connect(ui->droite,&QPushButton::released,this,&MyRobot::stop);
    connect(ui->gauche,&QPushButton::pressed,this,&MyRobot::gauche);
    connect(ui->gauche,&QPushButton::released,this,&MyRobot::stop);
    connect(ui->haut,&QPushButton::pressed,this,&MyRobot::avancer);
    connect(ui->haut,&QPushButton::released,this,&MyRobot::stop);
    connect(ui->bas,&QPushButton::pressed,this,&MyRobot::reculer);
    connect(ui->bas,&QPushButton::released,this,&MyRobot::stop);

    // affichage de la caméra
    QWebEngineView *video = new QWebEngineView();
    afficherCamera(video);

    // affichage des informations sur l'interface
    connect(&WifiBot, SIGNAL(updateUI(QByteArray)),this, SLOT(afficherInformation(QByteArray)));
    //afficherInformation();
}

MyRobot::~MyRobot()
{
    delete ui;
}

// bouton de connexion
void MyRobot::connection(){
    WifiBot.doConnect();
    etat = true;
}

// bouton de déconnexion
void MyRobot::deconnection(){
    WifiBot.disConnect();
    etat = false;
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

//Contrôle le déplacement du robot avec les différentes touches du clavier
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

void MyRobot::afficherInformation(QByteArray data){
    // regarde si le robot est connecté ou pas
    if(etat){

        // affichage de la batterie

        float batterie = float(data[2] >> 2);
        ui->vitesseDroite->display(int(batterie));


        // affichage de la vitesse

        float vit = float(-data[1] >> 8);
        ui->vitesseGauche->display(int(vit));

        // affichage des données infrarouge

        float infraDevant = float(data[11]);
        ui->infraDevant->display(abs(int(infraDevant)));
        float infraDeriere = float(data[12]);
        ui->infraDeriere->display(abs(int(infraDeriere)));
        float infraGauche = float(data[3]);
        ui->infraGauche->display(abs(int(infraGauche)));
        float infraDroite = float(data[4]);
        ui->infraDroite->display(abs(int(infraDroite)));


        // affichage de la position du robot

        float odometrieG = ((((long)data[8] << 24)) + (((long)data[7] << 16)) + (((long)data[6] <<8)) + ((long)data[5]));
        ui->odometrieG->display(int(odometrieG));

        float odometrieD = ((((long)data[16] << 24)) + (((long)data[15] << 16)) + (((long)data[14] << 8)) + ((long)data[13]));
        ui->odometrieD->display(int(odometrieD));

    }
}
