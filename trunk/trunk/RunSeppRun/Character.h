#ifndef CHARACTER_H
#define	CHARACTER_H

#include "WorldElement.h"
#include "Level.h"

class Character : public WorldElement {
public:
    Character();
    Character::Character(int, int, int, int);
    virtual void move(int, int);
protected:
    int life;

};

#endif

