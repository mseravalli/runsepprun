#ifndef LEVEL_H
#define	LEVEL_H

class Character;
class Block;
class Collect;
class Player;
class Egg;
class BackgroundElement;

#include <QtGui>
#include <string>
#include "Player.h"
#include "Egg.h"
#include "Enemy.h"

//!  Game level.
/*!
  This class is a collection of Block and Enemy and is the logical representation of the level. This class can generate its content by parsing xml level files.
*/
class Level
{
public:
    Level();
    ~Level();
    int isColliding(WorldElement&, int, int, int, int, int*);
    int parseXML(std::string);
    static int checkXML(std::string);

    QList<Block*>* getEnvironment();
    QList<Block*>* getFinalBlocks();
    QList<Enemy*>* getEnemies();
    QList<Collect*>* getCollects();
    QList<BackgroundElement*>* getBackgroundElements();
    int getLevelLength();
    bool checkEnd(int,int);

private:

    QList<Block*> environment;
    QList<Collect*> collects;
    QList<Enemy*> enemies;
    QList<BackgroundElement*> backgroundElements;
    QList<Block*> finalBlocks;
    int levelLength;
    int checkCollisionWith(WorldElement* , WorldElement&, int&, int&, int&, int&, int);

};

#endif
