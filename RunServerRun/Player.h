#ifndef PLAYER_H
#define	PLAYER_H

#include "Character.h"
class IsImmortalThread;
class Egg;

#include <QObject>

//!  Main character of the game.
/*!
  This class represents the main character of the game, which can be controlled by the user.
*/
class Player : public Character
{

    Q_OBJECT

public:
    Player(int, int, int, int, Level*, Egg**);
    void hit();
    void launch();
    void addPoints(int);
    int getPoints();
    int getEggs();
    void setEggs(int);
    void move();
    void rechargeEggs(int);
    void setEnded(bool);
    bool isEnded();

signals:
    void reachedEnd();


private:
    int points;
    int eggs;
    bool ended;
    IsImmortalThread *isImmortalThread;

    Egg** eggList;
};

#endif

