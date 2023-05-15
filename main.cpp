#include "mainwindow.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyRobot WifiBot;

    WifiBot.doConnect();

    //WifiBot.readyRead();

    //WifiBot.disConnect();

    return a.exec();
}
