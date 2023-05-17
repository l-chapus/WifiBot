
#include "myrobot.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyRobot w;
    w.show();
    return a.exec();
}
