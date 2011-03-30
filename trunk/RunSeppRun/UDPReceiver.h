#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QThread>
#include <QtNetwork>

#include "Client.h"

class UDPReceiver : public QThread
{
public:
    UDPReceiver(Client*);
    ~UDPReceiver();

    void setRunning(bool);

private:

    Client* client;
    QUdpSocket *udpSocket;
    bool running;

    void run();
    void processData(QByteArray*);

};

#endif // UDPRECEIVER_H
