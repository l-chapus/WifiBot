
#include "robot1.h"
#include <iostream>
#include <QApplication>
#include <QObject>>

Robot1::Robot1()
{

}

void Robot1::avancer(){

}

void Robot1::reculer(){

}
void Robot1::tourner_gauche(){

}
void Robot1::tourner_droit(){

}

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

