#ifndef MYROBOT_H
#define MYROBOT_H

#include <QMainWindow>
#include "Robot.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MyRobot; }
QT_END_NAMESPACE

class MyRobot : public QMainWindow

{
    Q_OBJECT

public:
    MyRobot(QWidget *parent = nullptr);
    ~MyRobot();
    void keyPressEvent(QKeyEvent *event);
    void connection();
    void deconnection();

private:
    Ui::MyRobot *ui;
    Robot WifiBot;
    bool etat =false;

    void droit();
    void gauche();
    void avancer();
    void reculer();
    void stop();
    void afficherCamera(QWebEngineView *video);

public slots:
    void afficherInformation(QByteArray data);

};

#endif // MYROBOT_H
