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

    // gestion de connexion du robot
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

    // affichage et mise à jour des informations sur l'interface
    connect(&WifiBot, SIGNAL(updateUI(QByteArray)),this, SLOT(afficherInformation(QByteArray)));
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

// fonctions pour déplacer le robot
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

// Affichage de la caméra
void MyRobot::afficherCamera(QWebEngineView *video){
    video -> setGeometry(0,0,451,481);
    QUrl url = QUrl("http://192.168.1.106:8080/?action=stream");
    video->load(url);
    video->setParent(ui->cam);
    video->show();
}

void MyRobot::afficherInformation(QByteArray data){
    // regarde si le robot est connecté ou pas
    if(etat){

        // affichage de la batterie

        float batterie = float(data[2] >> 2);
        if(batterie < 0){
            batterie += 255;
        }
        batterie = (batterie*100)/255 ;
        ui->lcdBatterie->display(int(batterie));


        // affichage de la vitesse

        float vitGauche = float(data[0]);
        ui->vitesseGauche->display(int(vitGauche));
        float vitDroite = float(data[9]);
        ui->vitesseDroite->display(int(vitDroite));


        // affichage des données infrarouge

        float infraHautDroit = float(data[11]);
        ui->infraHautDroit->display(abs(int(infraHautDroit)));
        float infraBasGauche = float(data[12]);
        ui->infraBasGauche->display(abs(int(infraBasGauche)));
        float infraHautGauche = float(data[3]);
        ui->infraHautGauche->display(abs(int(infraHautGauche)));
        float infraBasDroit = float(data[4]);
        ui->infraBasDroit->display(abs(int(infraBasDroit)));


        // affichage de la position du robot

        float odometrieG = ((((long)data[8] << 24)) + (((long)data[7] << 16)) + (((long)data[6] << 8)) + ((long)data[5]));
        ui->odometrieG->display(odometrieG);

        float odometrieD = ((((long)data[16] << 24)) + (((long)data[15] << 16)) + (((long)data[14] << 8)) + ((long)data[13]));
        ui->odometrieD->display(int(odometrieD));

    }
}
