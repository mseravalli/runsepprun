#include "Egg.h"
#include "WorldElement.h"
#include "Player.h"
#include "Level.h"
#include "Globals.h"
#include "Enemy.h"

//! The Constructor.
/*!
    It is called each time a new egg is created, this happens when the level is loaded. The constructor initializes the size, position and appearance of the egg
*/
Egg::Egg(int x, int y, int w, int h, Player* p, Level* l) : WorldElement(x, y, w, h, l)
{
    player = p;
    currentForceY = GRAVITY_FORCE;
    this->velocityX = EGG_X_VELOCITY;
    this->velocityY = EGG_Y_VELOCITY;
    launched = false;
    this->setVisible(false);
}

Egg::~Egg(){};

//! move.
/*!
    This function is called in order to change the position of an egg if it is launched. Move is called by advance of the corresponding graphicsItem
*/
void Egg::move()
{
    currentForceY *= GRAVITY_FORCE;
    this->posX = this->posX + (velocityX);
    this->posY = this->posY + (currentForceY + velocityY);

    int isColliding= level->isColliding(*this,this->posX,this->posY, width, height, &collisionIndex);

    //if the egg hits an enemy eliminate the enemy
    if(isColliding == DEATHLY_COLLIDING)
    {
        level->getEnemies()->at(collisionIndex)->setLife(level->getEnemies()->at(collisionIndex)->getLife() -1);
        this->setVisible(false);
    }

    //if the egg hits a block, eliminate the egg
    else if(isColliding == ENVIRONMENT_COLLIDING || isColliding == IMMEDIATE_DEATH)
    {
        this->setVisible(false);
    }
}

//! launch.
/*!
    This function is called in order to launch an egg. It determines from where and in which direction an egg is launched.
*/
void Egg::launch(int dir)
{
    velocityX*= dir;
    this->posX = player->getX()+( player->getWidth()/2);
    this->posY = player->getY() +(player->getHeight()/2);
    launched = true;
    this->setVisible(true);
}

void Egg::recharge()
{
    currentForceY = GRAVITY_FORCE;
    this->velocityX = EGG_X_VELOCITY;
    this->velocityY = EGG_Y_VELOCITY;
    this->launched = false;
    this->setVisible(false);
}

//! isLaunched.
/*!
    This function is as simple getter which returns whether the egg has been launched or not
*/
bool Egg::isLaunched()
{
    return launched;
}




