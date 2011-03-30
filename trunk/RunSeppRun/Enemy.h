#ifndef ENEMY_H
#define	ENEMY_H

#include "Character.h"

class Enemy : public Character {
public:
    Enemy();
    Enemy(int, int, int, int);
    void move(int, int);
private:

};

#endif

