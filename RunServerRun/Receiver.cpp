#include <QtNetwork>
#include <QtDebug>

#include "Receiver.h"
#include "Globals.h"
#include "Server.h"
#include "LogicEngine.h"
#include <cstdlib>


//! Creates a new object without making the socket listen.
Receiver::Receiver(Server *server)
{
    this->server = server;
    udpSocket = new QUdpSocket();
}

//! Unbinds the socket and destroys the object.
Receiver::~Receiver()
{
    unBind();
    delete udpSocket;
    udpSocket = NULL;
}

//! Binds the socket.
int Receiver::bind()
{
    if(!udpSocket->bind(SERVER_INCOMING_PORT_UDP, QUdpSocket::DontShareAddress))
        return 1;

    if(!connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams())))
        return 2;

    return 0;
}


//! Unbinds the socket
void Receiver::unBind()
{
    udpSocket->close();
}

//! Processes incoming packets.
void Receiver::processPendingDatagrams()
{

    while( udpSocket->hasPendingDatagrams() )
    {
        QByteArray *datagram = new QByteArray(udpSocket->pendingDatagramSize(), (char) 0);

        if( udpSocket->readDatagram(datagram->data(), datagram->size(), NULL, NULL) != -1)
        {
            processData(datagram);

        }
        else
        {
            qDebug() << "Non dovrebbe mai succedere.";
        }
        delete datagram;
    }
}

//! Updates the positions of the players.
void Receiver::processData(QByteArray* datagram)
{
    if(!server->getLogic()->isReady())
        return;

    int index = validClient(datagram);

    if(datagram->at(0) == KEY_INPUT_PACKET && datagram->size() == KEY_INPUT_PACKET_SIZE && index != -1)
    {
        Player *p = server->getClientList()->at(index)->player;

        if(p == NULL)
            return;

        int velocityFactor = (unsigned char) datagram->at(2);
        if(velocityFactor == 255)
            p->setVelocityX(-1 * PLAYER_X_VELOCITY);
        else if(velocityFactor == 1)
            p->setVelocityX(PLAYER_X_VELOCITY);
        else
            p->setVelocityX(0);

        if(((unsigned char) datagram->at(3)) == 1)
            p->setIsWillingToJump(true);
        else
            p->setIsWillingToJump(false);


        if(((unsigned char) datagram->at(4)) == 1)
            p->launch();
    }
    else
    {
        qDebug() << "Wrong packet: " << datagram->at(0) << (unsigned char) datagram->size();
    }

    return;
}

//! Check if packet comes from a valid client
int Receiver::validClient(QByteArray *data){
    for(int i = 0; i<server->getClientList()->size();i++){

        if(server->getClientList()->at(i)->id == (unsigned char)data->at(1)){
            return i;
        }

    }
    return -1;
}
