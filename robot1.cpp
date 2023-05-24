
#include "robot1.h"
#include <iostream>
#include <QApplication>

short Crc16(unsigned char *Adresse_tab , unsigned char Taille_max)
{
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int Cptbit = 0;
    unsigned int Parity = 0;

    Crc = 0xFFFF;
    Polynome = 0xA001;

    for ( CptOctet=0 ; CptOctet < Taille_max ; CptOctet++)
    {
        Crc ^= *( Adresse_tab + CptOctet);

        for ( Cptbit = 0; Cptbit <= 7 ; Cptbit++)
        {
            Parity= Crc;
            Crc >>= 1;
            if (Parity %2 ==true)
            {
                Crc ^= Polynome;
            }
        }
    }

    return(Crc);
}

Robot1::Robot1(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0; //vitesse droite
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0; //vitesse gauche
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}



//Fonction d'envoie du crc
void Robot1::crcToSend(){
    unsigned char *dat=(unsigned char *)DataToSend.data();
    short crc = Crc16(dat+1,6);
    DataToSend[7] = (char) crc;
    DataToSend[8] = (char) (crc >>8);
    DataReceived.resize(21);
    // setup signal and slot
}

void Robot1::avancer(){
    DataToSend[2] = 100;
    DataToSend[3] = 100 >> 8;
    DataToSend[4] = 100;
    DataToSend[5] = 100 >> 8;
    DataToSend[6] = 80;
    // on calcul le crc et on l'envoi
    crcToSend();
}

float Robot1::test(){
    unsigned char data = (DataReceived[1] >> 8);
    float bat = float(data);
    return bat;
}

void Robot1::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.10.1", 5008); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);

}

void Robot1::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void Robot1::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void Robot1::disconnected() {
    qDebug() << "disconnected...";
}

void Robot1::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void Robot1::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    unsigned char data = (DataReceived[2] >> 2);
    float bat = float(data);
    qDebug() << bat;
    //qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
}

void Robot1::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

