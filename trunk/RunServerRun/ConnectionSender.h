#ifndef CONNECTIONSENDER_H
#define CONNECTIONSENDER_H

#include <QtNetwork>
#include <QtCore>

class Server;

//! Send elements information to the client.
/*!
        This thread sends the information about the players, enemies, eggs, collectables over UDP to the client every SEND_INT milliseconds
 */
class ConnectionSender : public QThread
{

public:
    ConnectionSender(Server*);
    ~ConnectionSender();

    void stopSend();

    void run();

private:
    Server* server;

    QUdpSocket *udpSocket;
    bool running;

    void send();
};

#endif
