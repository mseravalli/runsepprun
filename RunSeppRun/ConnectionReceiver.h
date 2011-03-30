#ifndef CONNECTIONRECEIVER_H
#define CONNECTIONRECEIVER_H

#include <QObject>
#include <QtNetwork>

#include "Client.h"

//Multicast
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

class QUdpSocket;
class Client;

class UDPReceiver : public QThread
{
    Q_OBJECT

public:
    UDPReceiver(Client*);
    ~UDPReceiver();

private:
    Client* client;
    QByteArray receivedLvl;
    int sock;
    struct sockaddr_in multicast_addr;
    struct ip_mreq mc_req;
    struct sockaddr_in;
    char message_received[200];
    int msgrecv_len;
    QUdpSocket *udpSocket;
    void processData(QByteArray*);
    void run();
};



#endif
