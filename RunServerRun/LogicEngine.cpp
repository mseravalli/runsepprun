#include "LogicEngine.h"
#include "Player.h"
#include "Level.h"
#include "Collect.h"
#include "Server.h"
#include "Connectionthread.h"

//! Creates a new stopped thread with no loaded level.
LogicEngine::LogicEngine(QList<clientListItem*>* clientList, Server* server)
{
    this->server = server;
    this->clientList = clientList;
    level = NULL;
    ready = false;
    currentLevel = "";

    running = false;
}

//! unloads the level and destroys the object.
LogicEngine::~LogicEngine()
{
    if(ready)
        unloadLevel();
}

//! Main cycle of the thread. It handles the behaviour of the objects in the level.
void LogicEngine::run()
{
    running = true;
    while(running)
    {
        msleep(TIMER_X_MSEC);

        moves();

        int noOfEndedPlayers = 0;

        for(int i = 0; i < clientList->size(); i++)
        {
            if(clientList->at(i)->player != NULL && clientList->at(i)->player->isEnded())
                noOfEndedPlayers++;
        }
/*
        // IF ALL PLAYERS ENDED UNLOAD LEVEL
        if(noOfEndedPlayers != 0 && noOfEndedPlayers == clientList->size() && isReady())
        {

            for(int i = 0; i < clientList->size(); i++)
            {
                clientList->at(i)->thread->sendNextLevelPacket();
            }

            server->sender->stopSend();
            server->dataReceiver->unBind();
            server->getLogic()->unloadLevel();
        }*/

    }
}

void LogicEngine::moves()
{


    for(int i = 0; i < clientList->size(); i++)
    {
        if(clientList->at(i)->player != NULL && !clientList->at(i)->player->isEnded())
            clientList->at(i)->player->move();
    }

    // Unload of level when level finishes is done here becouse signal interrupts flow in player->move() called above.
    // Therefore the check.
    if(ready == false)
        return;


    for(int i = 0; i < level->getEnemies()->size(); i++)
    {
        level->getEnemies()->at(i)->move();
    }

    for(int i = 0; i < clientList->size(); i++)
    {
        if(clientList->at(i)->eggs != NULL )
        {
            for(int j = 0; j < NO_OF_EGGS; j++)
            {
                if(clientList->at(i)->eggs[j] != NULL && clientList->at(i)->eggs[j]->isVisible())
                {
                    clientList->at(i)->eggs[j]->move();
                }
            }
        }
    }
}

//! Adds a player to the logic of the game and creates new eggs for it.
void LogicEngine::addPlayer(int index)
{


    clientList->at(index)->eggs = new Egg*[NO_OF_EGGS];

    clientList->at(index)->player = new Player(PLAYER_X, PLAYER_Y, PLAYER_WIDTH, PLAYER_HEIGHT, level, clientList->at(index)->eggs);

    for(int i = 0; i < NO_OF_EGGS; i++)
    {
        clientList->at(index)->eggs[i] = new Egg(PLAYER_X,PLAYER_Y,EGG_SIZE,EGG_SIZE, clientList->at(index)->player, level);
    }


}

//! Check if level is ready.
bool LogicEngine::isReady()
{
    return ready;
}

//! Return the filename of the current level
std::string LogicEngine::getCurrentLevel()
{
    return currentLevel;
}

//! Loads the level given its path.
void LogicEngine::loadLevel(std::string file)
{
    level = new Level();

    int status = level->parseXML(file);

    qDebug() << "Level loaded with: " << status;

    if(status == 0)
    {
            ready = true;
    }
    else
    {
        unloadLevel();
        return;
    }

    this->start();
}


//! unloads the level.
void LogicEngine::unloadLevel()
{
    qDebug() << "Level unloaded";

    currentLevel = "";
    ready = false;

    running = false;
    sleep(4);

    delete level;
    level = NULL;

    for(int i = 0; i < clientList->size(); i++)
    {
        delete clientList->at(i)->player;
        clientList->at(i)->player = NULL;
    }

    return;
}

//! Sets the name of the current level.
void LogicEngine::setCurrentLevel(std::string l)
{
    currentLevel = l;
}

//! Returns a collection of information of the players, enemies, eggs and collectables that are sent periodically to the client.
QByteArray* LogicEngine::getActualPositions()
{
    QByteArray* positions = new QByteArray;

    positions->append( (char) level->getEnemies()->size() );

    for(int i = 0; i < level->getEnemies()->size(); i++)
    {
        // ID
        positions->append( '\0' ); // ID ANCORA DA FARE

        // X  COORDINATE
        int x = level->getEnemies()->at(i)->getX();

        int t1 = x / (256);
        int t2 = x % (256);

        positions->append( (char) t1 );
        positions->append( (char) t2 );

        // Y COORDINATE
        x = level->getEnemies()->at(i)->getY();

        t1 = x / 256;
        t2 = x % 256;

        positions->append( (char) t1 );
        positions->append( (char) t2 );

        // REST
        positions->append( (char) level->getEnemies()->at(i)->getDirectionX() );
        positions->append( (char) level->getEnemies()->at(i)->getDirectionY() );
        positions->append( (char) level->getEnemies()->at(i)->isVisible() );
    }


    int players = 0;

    for(int i = 0; i < clientList->size(); i++)
    {
        if(clientList->at(i)->player != NULL)
            players++;
    }

    positions->append( (char) players );

    for(int i = 0; i < clientList->size(); i++)
    {
        if(clientList->at(i)->player == NULL)
            continue;

        // ID
        positions->append( (char) clientList->at(i)->id );

        // X  COORDINATE
        int x = clientList->at(i)->player->getX();

        int t1 = x / 256;
        int t2 = x % 256;

        positions->append( (char) t1 );
        positions->append( (char) t2 );

        // Y COORDINATE
        x = clientList->at(i)->player->getY();

        if(x < 0)
        {
            x *= -1;
            x += 1000;
        }

        t1 = x / 256;
        t2 = x % 256;

        positions->append( (char) t1 );
        positions->append( (char) t2 );

        // REST

        int dirX = 0;

        if (clientList->at(i)->player->getVelocityX() != 0){
        	dirX = clientList->at(i)->player->getDirectionX();
        }

        positions->append( (char) dirX );
        positions->append( (char) clientList->at(i)->player->getDirectionY() );

        positions->append( (char) clientList->at(i)->player->getLife() );

        // Points
        x = clientList->at(i)->player->getPoints();
        t1 = x / 256;
        t2 = x % 256;
        positions->append( (char) t1 );
        positions->append( (char) t2 );

        positions->append( (char) clientList->at(i)->player->getEggs() );

        positions->append( (char) clientList->at(i)->player->isVisible() );
    }

    // Reserve position for size
    positions->append( '\0' );

    int pos = positions->size() -1;

    int eggs = 0;

    for(int i = 0; i < clientList->size(); i++)
    {
        if(clientList->at(i)->player == NULL)
            continue;

        for(int j = 0; j < NO_OF_EGGS; j++)
        {
            if(clientList->at(i)->eggs[j]->isVisible())
            {
                eggs++;

                // X  COORDINATE
                int x =  clientList->at(i)->eggs[j]->getX();

                int t1 = x / 256;
                int t2 = x % 256;

                positions->append( (char) t1 );
                positions->append( (char) t2 );

                // Y COORDINATE
                x = clientList->at(i)->eggs[j]->getY();

                t1 = x / 256;
                t2 = x % 256;

                positions->append( (char) t1 );
                positions->append( (char) t2 );

                // REST
                positions->append( (char) clientList->at(i)->eggs[j]->isVisible() );
            }
        }
    }

    (*positions)[pos] = (char) eggs;


    // Collectables
    positions->append( (char) level->getCollects()->size() );

    for(int i = 0; i < level->getCollects()->size(); i++)
    {
        positions->append( (char) level->getCollects()->at(i)->isVisible() );
    }

    return  positions;
}

