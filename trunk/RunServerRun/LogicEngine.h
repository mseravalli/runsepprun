#ifndef LOGICENGINE_H_
#define LOGICENGINE_H_

class Level;
class Server;
#include <string>
#include "Globals.h"
#include <QtCore>


//! Handles the game logic.
/*!
        This thread continuously updates the positions of the enemies and the players and handles the flow of the game.
 */
class LogicEngine : public QThread
{

public:
    LogicEngine(QList<clientListItem*>*, Server*);
    ~LogicEngine();
    void addPlayer(int);
    bool isReady();

    void loadLevel(std::string);
    void unloadLevel();

    std::string getCurrentLevel();
    void setCurrentLevel(std::string);

    QByteArray* getActualPositions();

    void run();



private:
    Level* level;
    bool ready;
    QList<clientListItem*>* clientList;
    Server* server;
    std::string currentLevel;
    bool running;

    void moves();
};

#endif
