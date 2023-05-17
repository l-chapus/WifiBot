#include "Robot.h"

#include <QApplication>
#include <iostream>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyRobot WifiBot;

    WifiBot.doConnect();

    WifiBot.avancer();
    std::cout << "Données reçues (hexadécimal) : " << WifiBot.test() << std::endl;;

    //WifiBot.disConnect();

    return a.exec();
}

