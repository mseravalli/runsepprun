#ifndef CONNECTIONRECEIVER_H
#define CONNECTIONRECEIVER_H

#include <QtCore>
#include <QtNetwork>
class Server;

//! Accepts incoming connections
/*!
    This thread listens on a TCP port and accepts incoming connections from the clients. A ConnetionThread is created for each accepted client.
 */
class ConnectionReceiver : public QThread
{
    Q_OBJECT

public:
    ConnectionReceiver(Server *server);
    ~ConnectionReceiver();
    int bind();
    void unBind();
    void setAccepting(bool);


private:
    void run();
    bool running;
    bool accepting;

    QTcpServer *tcpServer;

    Server *server;
};



#endif
