#include "Robot.h"
#include "myrobot.h"

#include <QApplication>
#include <iostream>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Robot WifiBot;

    //WifiBot.doConnect();

    //WifiBot.avancer();

    //WifiBot.disConnect();

    MyRobot w;
    w.show();

    return a.exec();
}

