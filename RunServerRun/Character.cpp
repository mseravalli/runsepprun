#include "Character.h"
#include "WorldElement.h"
#include "Level.h"
#include "Globals.h"
#include <string>
#include <iostream>
#include "Collect.h"

/*!
  Create a new Character by specifying its position, level in which it is contained.
*/
Character::Character(int x, int y, int w, int h, Level* l) : WorldElement::WorldElement(x, y, w, h, l)
{
        //velocità con cui il personaggio cade - qua si puo giocare per farlo salire di più e più lentamente
        jumping_force = 0;
        this->isAbleToJump = false;

        //velocità con cui il personaggio spicca il salto iniziale
        velocityY = 1;
}

//!  It moves the character.
/*!
  This method calculates and sets the position of the character during the movement or jump.
*/
void Character::move(int& isCollidingBottom, int& isCollidingFront,int& isCollidingTop, int& collisionIndex)
{

    if(life == 0)
    {
        this->setVisible(false);
        return;
    }

    //the actual height of the character is stored
    //int realHeight = height;

    //the height becomes 0 and the character is checked just as a line
    //then its height is restored
    //height = 0;
    //double tmp = round (posY + velocityY + jumping_force);
    isCollidingTop = level->isColliding( *this, posX, /*tmp*/round (posY + velocityY + jumping_force) , width, 0, &collisionIndex);
    //height = realHeight;

    //the height becomes 0 and the character is checked just as a line
    //then its height is restored
    //posY += realHeight;
    //height = 0;
    //tmp = round (posY + velocityY + jumping_force);
    isCollidingBottom = level->isColliding( *this, posX, /*tmp*/round (posY + height + velocityY + jumping_force) , width, 0, &collisionIndex);
    //height = realHeight;
    //posY -= realHeight;

    //if it is not moving the player is enlarged of a pixel and the collision
    //check is perfomrmed
    if(velocityX == 0){
        //posX -=1;
        //width +=2;
        isCollidingFront = level->isColliding( *this, posX + velocityX - 1, posY, width + 2, height, &collisionIndex);
        //width -=2;
        //posX +=1;

    //if the player is moving the collision check is performed normally
    }
    else
    {
        isCollidingFront = level->isColliding( *this, posX + velocityX, posY, width, height, &collisionIndex);
    }


    if(isCollidingBottom == IMMEDIATE_DEATH || isCollidingFront == IMMEDIATE_DEATH || isCollidingTop == IMMEDIATE_DEATH)
    {
        this->setVisible(false);
        return;
    }



    //if it is not on a floor (not colliding bottom)
    if( isCollidingBottom == NOT_COLLIDING || isCollidingBottom == COLLECTABLE_COLLIDING)
    {
        posY += (velocityY + jumping_force);

        velocityY *=GRAVITY_FORCE;

        this->isAbleToJump = false;
        this->isWillingToJump = false;

    }

    if(isCollidingBottom == ENVIRONMENT_COLLIDING || isCollidingBottom == DEATHLY_COLLIDING)
    {
            this->isAbleToJump = true;
            jumping_force = 0;
            velocityY = 1;
    }

    if(isCollidingTop == ENVIRONMENT_COLLIDING || isCollidingTop == DEATHLY_COLLIDING)
    {
            this->isAbleToJump = false;
            jumping_force = 0;
            velocityY = 1;
    }


    //if it wants and it is able jump
    if (this->isWillingToJump && this->isAbleToJump)
    {
            jumping_force = jumpHeight;
            posY += (velocityY + jumping_force);
            this->isAbleToJump = false;
            this->isWillingToJump = false;
    }

    //if it is colliding either on the left or on the right
    if(isCollidingFront == NOT_COLLIDING || isCollidingFront == COLLECTABLE_COLLIDING)
    {
        this->posX += velocityX;
    }

}

/*!
   sets the willing of jump
 */
void Character::setIsWillingToJump(bool wantsToJump)
{
	this->isWillingToJump = wantsToJump;
}

//! Returns the X moving direction
int Character::getDirectionX()
{
        return directionX;
}

//! Returns true if the player is in a position where it is allowed to jump.
bool Character::getIsAbleToJump()
{
    return isAbleToJump;
}

//! Returns the force the actual jumping force
double Character::getJumpingForce()
{
    return jumping_force;
}

//! Return the number of lifes.
int Character::getLife()
{
    return life;
}

//! Sets the number of lifes.
void Character::setLife(int life)
{
    this->life = life;
}

