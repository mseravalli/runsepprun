#ifndef ENEMY_H
#define	ENEMY_H

#include "Character.h"

//!  Level enemies.
/*!
  This class represents the enemies in the level and handles its movements.
*/
class Enemy : public Character
{
public:
    Enemy(int, int, int, int, int, Level*);
    void move();
private:

};

#endif

