#include "Server.h"
#include "ConnectionReceiver.h"
#include "ConnectionSender.h"
#include "LogicEngine.h"
#include "Arch.h"
#include "Level.h"

//! Create a new server
Server::Server(int noPlayers)
{
    this->noPlayers = noPlayers;

    clientList = new QList<clientListItem*>();
    receiver = new ConnectionReceiver(this);
    dataReceiver = new Receiver(this);
    sender = new ConnectionSender(this);
    levelList = new QList<QString>;
    logic = new LogicEngine(clientList, this);

    loadLevels();
}

//! Destroy the server
Server::~Server()
{
    delete clientList;
    clientList = NULL;
    delete receiver;
    receiver = NULL;
    delete sender;
    sender = NULL;
    delete logic;
    logic = NULL;
    delete dataReceiver;
    dataReceiver = NULL;
}

//! Starts listening
int Server::start()
{
    return receiver->bind();
}

//! Returns the list of clients.
QList<clientListItem*>* Server::getClientList()
{
    return clientList;
}

//! Returns the number of players.
int Server::getNoPlayers()
{
    return noPlayers;
}

//! Returns the logic engine.
LogicEngine* Server::getLogic()
{
    return logic;
}

//! Returns the list of levels.
QList<QString>* Server::getLevels()
{
    return levelList;
}

//! Extracts the levels in the directory ./levels and adds them to the lst of levels.
void Server::loadLevels()
{

    //QDir().mkdir(LEVEL_DIR);

    QDir dirArch(LEVEL_SOURCE_DIR, "*.level", QDir::Name, QDir::Files);
    QStringList files = dirArch.entryList();

    for(int i  = 0; i < files.size(); i++)
    {
        QString fileName("");
        fileName.append(LEVEL_SOURCE_DIR);
        fileName.append("/");
        fileName.append(files.at(i));
        extract(fileName);
    }

    QDir dirLvl(LEVEL_DIR, "*.xml", QDir::Name, QDir::Files);
    files = dirLvl.entryList();

    for(int i  = 0; i < files.size(); i++)
    {
        QString fileName("");
        fileName.append(LEVEL_DIR);
        fileName.append("/");
        fileName.append(files.at(i));

        int status = Level::checkXML(fileName.toStdString());
        if(status == 0)
            levelList->append(files.at(i));
        else
            qDebug() << "Corrupt file: " << fileName << "error: " << status;
    }

    if(levelList->size() == 0)
    {
        receiver->unBind();

        qDebug() << "No levels could be loaded. Missing or corrupt files. Exiting.....";

        delete this;
        exit(1);
    }

}
