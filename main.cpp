#include "Robot.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyRobot WifiBot;

    WifiBot.doConnect();

    //WifiBot.test();

    //WifiBot.disConnect();

    return a.exec();
}
