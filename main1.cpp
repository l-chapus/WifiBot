
#include "myrobot.h"
#include "robot1.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyRobot w;
    w.show();

    //Robot1 WifiBot;

    //WifiBot.doConnect();

    //WifiBot.avancer();
    //std::cout << "Données reçues (hexadécimal) : " << WifiBot.test() << std::endl;

    //WifiBot.disConnect();

    return a.exec();
}
