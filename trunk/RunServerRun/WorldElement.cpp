#include "WorldElement.h"
#include "Level.h"
#include "Player.h"
#include "Globals.h"

WorldElement::WorldElement(int x, int y, int w, int h, Level* l)
{
    this->posX = x;
    this->posY = y;
    this->width = w;
    this->height = h;
    this->velocityX = 0;
    this->velocityY = 0;
    this->level = l;
    this->directionX = RIGHT_DIRECTION;
    this->directionY = NO_DIRECTION;
    this->isImmortal = false;
    visible = true;
}

int WorldElement::getX()
{
    return this->posX;
}

int WorldElement::getY()
{
    return this->posY;
}

int WorldElement::getHeight()
{
    return this->height;
}

int WorldElement::getWidth()
{
    return this->width;
}

void WorldElement::setVisible(bool v)
{
    visible = v;
}


bool WorldElement::isVisible()
{
    return visible;
}

/*!
  It sets the amount of pixels that the element moves on the x axis, and as
  collateral event the direction is set correctly, if the player stops the direction
  will remain the last one
*/
void WorldElement::setVelocityX(double velX)
{
    this->velocityX = velX;

    if( velX > 0)
       this->directionX = RIGHT_DIRECTION;

    else if (velX < 0)
        this->directionX = LEFT_DIRECTION;
}

double WorldElement::getVelocityX(){
	return this->velocityX;
}

void WorldElement::move()
{
}

double WorldElement::round(double x)
{
    if(x>=0.5){return ceil(x);}else{return floor(x);}
}


int WorldElement::getDirectionX()
{
    return directionX;
}

int WorldElement::getDirectionY()
{

    //qDebug() << velocityY +jumping_force;

    if(this->velocityY +jumping_force<0 && !isAbleToJump)
    {
        this->directionY = UP_DIRECTION;
    }
    else if(this->velocityY +jumping_force>0 && !isAbleToJump)
    {
        this->directionY = DOWN_DIRECTION;
    }
    else
    {
        this->directionY = NO_DIRECTION;
    }
    return directionY;
}


bool WorldElement::getIsAbleToJump()
{
    return isAbleToJump;
}

double WorldElement::getJumpingForce()
{
    return 0;
}

bool WorldElement::getIsImmortal()
{
    return isImmortal;
}
