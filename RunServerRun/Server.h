#ifndef SERVER_H
#define SERVER_H

#include "ConnectionSender.h"
#include <QtCore>
#include "Globals.h"
#include "Receiver.h"
class Receiver;
class ConnectionReceiver;
class ConnectionSender;
class LogicEngine;
class Level;

//! Handles server behaviour.
/*!
         The main class that handles all the elements of the server.
 */
class Server
{
public:
    Server(int);
    ~Server();
    int start();
    QList<clientListItem*>* getClientList();
    int getNoPlayers();
    LogicEngine* getLogic();
    QList<QString>* getLevels();

    ConnectionReceiver *receiver;
    Receiver *dataReceiver;
    ConnectionSender *sender;

private:
    QList<clientListItem*>* clientList;
    LogicEngine *logic;
    int noPlayers;
    QList<QString>* levelList;
    void loadLevels();

};

#endif
