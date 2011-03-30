#include "ConnectionSender.h"
#include "Globals.h"
#include "Server.h"
#include "LogicEngine.h"

/*!
 * the thread is contructed
 */
ConnectionSender::ConnectionSender(Server *s)
{
    running = false;
    server = s;
    udpSocket = new QUdpSocket();
    udpSocket->moveToThread(this);
}

//! Closes the socket and destroyes the object.
ConnectionSender::~ConnectionSender()
{
    stopSend();
    udpSocket->close();

    delete udpSocket;
    udpSocket = NULL;
}

//! Stops the thread.
void ConnectionSender::stopSend()
{
    running = false;
    sleep(4);
}

/*!
 * The thread starts, the threads sleeps for a time seconds
 */
void ConnectionSender::run()
{
    running = true;

    while(running)
    {
        msleep(SEND_INT);

        send();
    }
}

void ConnectionSender::send()
{
    QByteArray* packet = server->getLogic()->getActualPositions();

    packet->prepend(ITEM_PACKET);

    for(int i = 0; i < server->getClientList()->size(); i++)
    {
        if(udpSocket->writeDatagram(*packet, server->getClientList()->at(i)->ip, CLIENT_INCOMING_PORT_UDP + server->getClientList()->at(i)->id) == -1)
            qDebug() << "Could not send update packet";
    }

    delete packet;
}
