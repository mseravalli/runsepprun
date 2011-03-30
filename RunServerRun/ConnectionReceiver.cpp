#include <QtNetwork>
#include <QtDebug>

#include "ConnectionReceiver.h"
#include "Globals.h"
#include "Server.h"
#include "LogicEngine.h"
#include <cstdlib>
#include "Connectionthread.h"

//! Constructs a new ConectionReceiver
ConnectionReceiver::ConnectionReceiver(Server *server)
{
    this->server = server;
    tcpServer = new QTcpServer;
    running = false;
}

//! Unbinds the Socket and deletes the object.
ConnectionReceiver::~ConnectionReceiver()
{
    unBind();
    delete tcpServer;
    tcpServer = NULL;
}

//! Starts listen on TCP
int ConnectionReceiver::bind()
{    
    if(!tcpServer->listen(QHostAddress::Any, SERVER_INCOMING_PORT_TCP))
        return 1;

    tcpServer->moveToThread(this);

    running = true;
    accepting = true;

    start();

    return 0;
}

//! Receives the connections and creates a new ConnectionThread for each client.
void ConnectionReceiver::run()
{
    while(running)
    {
        if(tcpServer->waitForNewConnection(-1, NULL))
        {
            if(!accepting)
            {
                QTcpSocket* s = tcpServer->nextPendingConnection();

                s->disconnectFromHost();

                delete s;
                continue;
            }

            qDebug() << "Clientconnected";

            ConnectionThread* connection = new ConnectionThread(tcpServer->nextPendingConnection(), server);
            connection->start();
        }
    }
}

//! Stops listening on the TCP port
void ConnectionReceiver::unBind()
{
    running = false;
    accepting = false;
    quit();

    //sleep(4);
    //tcpServer->close();
}

//! Sets whether the server should accept incoming TCP connections
void ConnectionReceiver::setAccepting(bool accepting)
{
    this->accepting = accepting;
}


