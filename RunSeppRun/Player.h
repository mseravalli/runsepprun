#ifndef PLAYER_H
#define	PLAYER_H

#include "Character.h"

class Player : public Character {
public:
    Player();
    void move(int, int);
    void hit();
    void launch();
private:

};

#endif

