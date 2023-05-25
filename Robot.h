#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>

#include <QWebEngineView>

class Robot : public QObject {
    Q_OBJECT
public:
    explicit Robot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;
    void crcToSend();
    void avancer();
    void reculer();
    void gauche();
    void droite();
    void stop();

signals:
    void updateUI(const QByteArray Data);

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();

private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
};

#endif // ROBOT_H
