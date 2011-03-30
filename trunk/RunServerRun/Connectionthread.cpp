#include "Connectionthread.h"
#include "Globals.h"
#include "Server.h"
#include "LogicEngine.h"
#include "Egg.h"
#include "ConnectionReceiver.h"

//QMutex ConnectionThread::mutex;

//! Creates a new thread and assignes a connected socket to it.
ConnectionThread::ConnectionThread(QTcpSocket* socket, Server *server)
{
    this->socket = socket;
    socket->setParent(NULL);
    socket->moveToThread(this);

    this->server = server;

}

ConnectionThread::~ConnectionThread()
{
}


void ConnectionThread::cleanupAndTerminate()
{
    qDebug() << "Client disconnected: ";
    socket->close();
    socket->deleteLater();
    
    for(int i = 0; i < server->getClientList()->size(); i++)
    {
        if(server->getClientList()->at(i)->thread == this)
        {
            delete server->getClientList()->at(i)->player;
            server->getClientList()->at(i)->player = NULL;

            if(server->getClientList()->at(i)->eggs != NULL)
                for(int j = 0; j < NO_OF_EGGS; j++)
                {
                    delete server->getClientList()->at(i)->eggs[j];
                    server->getClientList()->at(i)->eggs[j] = NULL;
                }

            server->getClientList()->removeAt(i);
            break;
        }
    }

    if(server->getClientList()->isEmpty())
    {
        qDebug() << "Unbindung";
        server->receiver->setAccepting(false);

        server->sender->stopSend();
        server->dataReceiver->unBind();
        server->getLogic()->unloadLevel();

        qDebug() << "rebinding";
        server->receiver->setAccepting(true);
    }

    quit();

    this->deleteLater();

    return;
}

//! Sends the information that the level ended to the clients.
void ConnectionThread::sendEndPacket()
{
    QByteArray response;

    response.append(END_PACKET);

    if(socket->bytesToWrite() != 0)
    {
        socket->waitForBytesWritten(-1);
        socket->flush();
    }

    if(socket->write(response) == -1)
    {
        qDebug() << "Could not send end packet";
    }

    if(socket->bytesToWrite() != 0)
    {
        socket->waitForBytesWritten(-1);
        socket->flush();
    }

    qDebug() << "End packet sent";
}
/*
void ConnectionThread::sendNextLevelPacket()
{
    QByteArray response;

    response.append(NEXT_LEVEL_PACKET);
    response.append((char)server->getClientList()->at(0)->id);

    if(socket->bytesToWrite() != 0)
    {
        socket->waitForBytesWritten(-1);
        socket->flush();
    }

    if(socket->write(response) == -1)
    {
        qDebug() << "Could not send next level packet";
    }

    if(socket->bytesToWrite() != 0)
    {
        socket->waitForBytesWritten(-1);
        socket->flush();
    }

    qDebug() << "Next level packet sent";
}*/


void ConnectionThread::run()
{
    while( socket->waitForReadyRead(-1) )
    {
        QByteArray *datagram = new QByteArray();

        datagram->append(socket->read(1));

        if(datagram->at(0) == HELLO_PACKET)
            datagram->append(socket->read(HELLO_PACKET_SIZE - 1));
        else if(datagram->at(0) == ACK_PACKET)
            datagram->append(socket->read(ACK_PACKET_SIZE - 1));
        else if(datagram->at(0) == LEVEL_ID_PACKET)
            datagram->append(socket->read(LEVEL_ID_PACKET_SIZE - 1));
        else if(datagram->at(0) == ACK2_PACKET)
            datagram->append(socket->read(ACK2_PACKET_SIZE - 1));
        else if(datagram->at(0) == READY_PACKET)
            datagram->append(socket->read(READY_PACKET_SIZE - 1));
        else
        {
            qDebug() << "Early read or unnown packet.";

            delete datagram;

            socket->disconnectFromHost();

            cleanupAndTerminate();
            return;
        }

        QList<QByteArray> *response = new QList<QByteArray>;

        if(!datagram->isEmpty())
        {
            processData(datagram, response);

            if(!response->isEmpty())
            {
                for(int i = 0; i < response->size(); i++)
                {
                    if(socket->write(response->at(i)) == -1)
                    {
                        qDebug() << "Could not send packet" << response->at(0);
                    }
                    socket->waitForBytesWritten(-1);
                    socket->flush();

                    if(response->at(i).at(0) == ID_PACKET && response->at(i).at(2) == ID_PACKET_RIGHTS_VFC)
                    {
                        socket->disconnectFromHost();

                        delete response;
                        delete datagram;

                        cleanupAndTerminate();

                        return;
                    }
                }
            }

        }
        else
        {
            qDebug() << "Could not read packet.";
        }

        delete response;
        delete datagram;
    }
    qDebug() << "Socket state: " << socket->error();
    cleanupAndTerminate();
}

void ConnectionThread::processData(QByteArray* datagram, QList<QByteArray>* response)
{

    if(datagram->at(0) == HELLO_PACKET && datagram->size() == HELLO_PACKET_SIZE)
    {
        QByteArray packet;
        clientListItem* newClient = new clientListItem;

        if((server->getNoPlayers() > server->getClientList()->size() && server->getLogic()->isReady()) || server->getClientList()->isEmpty())
        {
            if(server->getClientList()->isEmpty())
            {
                newClient->id = LEADER_PLAYER;
                newClient->player = NULL;
                newClient->eggs = NULL;
                newClient->state = UNNOWN_STATE;
                newClient->thread = this;
                newClient->ip = socket->peerAddress();
                server->getClientList()->append(newClient);
            }
            else
            {
                newClient->id = server->getClientList()->last()->id + 1;
                newClient->player = NULL;
                newClient->eggs = NULL;
                newClient->state = UNNOWN_STATE;
                newClient->thread = this;
                newClient->ip = socket->peerAddress();
                server->getClientList()->append(newClient);
            }

            packet.append(ID_PACKET);
            packet.append(newClient->id);

            if(server->getClientList()->size() == 1)
                packet.append(ID_PACKET_RIGHTS_NEW);
            else
                packet.append(ID_PACKET_RIGHTS_JOIN);

        }
        else
        {
            packet.append(ID_PACKET);
            packet.append(VFC_PLAYER);
            packet.append(ID_PACKET_RIGHTS_VFC);
        }
        response->append(packet);
    }
    else if(datagram->at(0) == ACK_PACKET && datagram->size() == ACK_PACKET_SIZE)
    {
        if(server->getLogic()->isReady())
        {
            qDebug() << "Cannot change level until not finished.";
            return;
        }

        if(datagram->at(1) != server->getClientList()->at(0)->id)
        {
            qDebug() << "Try action when not enough rights";
            return;
        }

        QList<QString>* levels= server->getLevels();
        QByteArray packet;

        int packetLength = 1;

        for(int i = 0; i < levels->size(); i++)
        {
            packetLength ++; //length of separator
            packetLength += levels->at(i).size(); //length of level name
        }


        for(int i = 0; i < levels->size(); i++)
        {
            for(int j = 0; j < levels->at(i).length(); j++)
            {
                packet.append(levels->at(i).at(j));
            }
            packet.append(SEPARATOR);
       }


        packet.prepend((char) packet.size());
        packet.prepend(LEVELLIST_PACKET);


        response->append(packet);
    }
    else if(datagram->at(0) == LEVEL_ID_PACKET && datagram->size() == LEVEL_ID_PACKET_SIZE)
    {
        if(datagram->at(1) != server->getClientList()->at(0)->id)
        {
            qDebug() << "Try action when not enough rights";
            return;
        }

        if(datagram->at(2) >= server->getLevels()->size())
        {
            qDebug() << "Try to load invalid level";
            return;
        }

        QString level = server->getLevels()->at((unsigned char)datagram->at(2));
        server->getLogic()->setCurrentLevel(level.toStdString());

        QString levelName("");
        levelName.append(LEVEL_DIR);
        levelName.append("/");
        levelName.append(level);

        server->getLogic()->loadLevel(levelName.toStdString());
        server->sender->start();
        connect(this, SIGNAL(startDataReceiver()),server->dataReceiver, SLOT(bind()));
        emit startDataReceiver();
    }
    else if(datagram->at(0) == ACK2_PACKET && datagram->size() == ACK2_PACKET_SIZE)
    {
        QString level(server->getLogic()->getCurrentLevel().c_str());

        if(!server->getLogic()->isReady())
        {
            qDebug() << "Got ack2 packet when level not loaded";
            return;
        }

        QString fileName("");
        fileName.append(LEVEL_SOURCE_DIR);
        fileName.append("/");
        fileName.append(level.left(level.size()-4));
        fileName.append(".level");


        QFile f( fileName );
        if (!f.open(QIODevice::ReadOnly))
        {
            qDebug() << "Could not open file for send: " << fileName;
            return;
        }

        QByteArray file = f.readAll();
        f.close();

        QByteArray p;
        p.append(LEVEL_PACKET);

        int t1 = file.size()/ (256*256*256);
        int t2 = (file.size() % (256*256*256)) / (256*256);
        int t3 = ((file.size() % (256*256*256)) % (256*256))  / 256;
        int t4 = ((file.size() % (256*256*256)) % (256*256))  % 256;

        p.append((char) t1);
        p.append((char) t2);
        p.append((char) t3);
        p.append((char) t4);

        p.append(file);

        response->append(p);
    }
    else if(datagram->at(0) == READY_PACKET && datagram->size() == READY_PACKET_SIZE)
    {
        if(!server->getLogic()->isReady())
        {
            qDebug() << "Got ready packet when level not loaded";
            return;
        }

        bool found = false;
        for(int i = 0; i < server->getClientList()->size(); i++)
        {
            if(datagram->at(1) == server->getClientList()->at(i)->id)
                found = true;
        }


        if(!found )
        {
            qDebug() << "Got ready packet with wrong id";
            return;
        }

        int index = -1;

        for(int i = 0; i < server->getClientList()->size(); i++)
        {
            if(server->getClientList()->at(i)->id == (unsigned char) datagram->at(1))
                index = i;

        }

        if(index != -1)
            server->getLogic()->addPlayer( index );
        else
        {
            qDebug() << "Wrong ready packet: unexistent id " << (unsigned char) datagram->at(1);
            return;
        }

        QObject::connect(server->getClientList()->at(index)->player, SIGNAL(reachedEnd()), this, SLOT(sendEndPacket()), Qt::DirectConnection);

    }
    else
    {
        qDebug() << "Wrong packet: " << datagram->at(0) << (unsigned char) datagram->size();
    }

    return;
}
