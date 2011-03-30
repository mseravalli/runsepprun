#ifndef CHARACTER_H
#define	CHARACTER_H

#include "WorldElement.h"

//!  Level characters.
/*!
  This class represents the player and the enemies of the level. It is responsible for its movement and for the gravity acting on them.
*/
class Character : public WorldElement
{
public:
    Character(int, int, int, int, Level*);
    virtual void move(int&, int&, int&, int&);
    void setIsWillingToJump(bool);
    int getDirectionX();
    bool getIsAbleToJump();
    double getJumpingForce();
    int getLife();
    void setLife(int);

protected:
    int life;
    bool isWillingToJump;
    double jumpHeight;
};

#endif

