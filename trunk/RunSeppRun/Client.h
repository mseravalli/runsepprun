#ifndef CLIENT_H
#define CLIENT_H

#include <QtGui>
#include <QtNetwork>
#include "MainWindow.h"
class UDPReceiver;
class UDPSender;

class Client: public QObject{

    Q_OBJECT

public:
    Client(MainWindow*);
    ~Client();

    void setServerAddress(QString, quint16);
    void connectToServer();
    void disconnectFromServer();

    QHostAddress* getServerAddress();

    QUdpSocket* getUDPSocket();
    MainWindow* getWindow();
    bool isReady();

    void setDirection(int);
    void setIsJumping(bool);
    void setIsLaunching(bool);
    void setLevelID(int);

    int getDirection();
    bool isJumping();
    bool isLaunching();
    int getID();

private slots:
    void startDialog();
    void errorHandler(QAbstractSocket::SocketError);
    void processDatagram();

private:
    MainWindow* window;
    QHostAddress* clientAddress;
    QHostAddress* serverAddress;
    quint16 serverPort;

    QString selectedLevel;

    QTcpSocket *tcpSocket;
    QUdpSocket *udpSocket;    

    int id;
    int levelID;

    int playerDirX;
    bool playerIsJumping;
    bool playerIsLaunching;

    bool ready;

    int levelComplete; // 0: no byte received yet; 1: all bytes received; -1: waiting for remaining bytes
    int levelSize;

    QByteArray *receivedLvl;

    UDPReceiver* receiver;
    UDPSender* sender;

    int sendSetupPacket(int);
    void processData(QByteArray*);
    int bind();

};

#endif // CLIENT_H
