#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QtNetwork>
#include "Player.h"
class Server;
class Player;
class QUdpSocket;

//! Receives the key inputs.
/*!
        This class listens to a UDP port. It recieves and handles the key inputs.
 */
class Receiver : public QObject
{
    Q_OBJECT

public:
    Receiver(Server *server);
    ~Receiver();

    void unBind();

private slots:
    void processPendingDatagrams();

public slots:
    int bind();

private:
    QUdpSocket *udpSocket;
    void processData(QByteArray*);
    Server *server;
    int validClient(QByteArray*);
};



#endif
