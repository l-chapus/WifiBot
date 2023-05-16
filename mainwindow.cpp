#include "mainwindow.h"
#include <windows.h>
#include "Robot.h"


void mainwindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z)
    {
        Robot.avancer();
    }
}
