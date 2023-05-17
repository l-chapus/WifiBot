#include "mainwindow.h"

#include <windows.h>
#include "Robot.h"


//MainWindow::MainWindow(QWidget *parent)
//    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//    ui->widget->load(QUrl(QString("http://192.168.10.1:8080/?action=stream")));
//    connect(&Robot, SIGNAL(updateUI(QByteArray)),this, SLOT(affichage(QByteArray)));
//}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z)
    {
        Robot.avancer();
    }
}
