#include "Player.h"
#include "Level.h"

#include "Character.h"
#include "WorldElement.h"
#include "Globals.h"
#include <string>
#include <iostream>
#include "Collect.h"
#include "Enemy.h"
#include "qdebug.h"
#include "IsImmortalThread.h"
#include "Egg.h"

/*!
  Create a new Player by specifying its position, size, color and level in which it is contained.
*/
Player::Player(int x, int y, int w, int h, Level* l, Egg** eggList) : Character(x, y, w, h, l)
{
    points = 0;
    eggs = NO_OF_EGGS;

    this->eggList = eggList;

    this->ended = false;

    this->directionX = RIGHT_DIRECTION;

    this->isImmortal = false;

    isImmortalThread = new IsImmortalThread(&isImmortal);

    jumpHeight = PLAYER_Y_VELOCITY;

    life = 3;
}

void Player::hit()
{

}

/*!
  Recharges the last "no" eggs of the array
*/

void Player::rechargeEggs(int no)
{
    if(eggs + no > NO_OF_EGGS)
    {
        eggs = NO_OF_EGGS;
    }
    else
    {
        eggs += no;
    }

    for(int i = 0, recharged = 0; i < NO_OF_EGGS && recharged < no ; i++)
    {
        if((*eggList[i]).isLaunched())
        {
            recharged++;
            (*eggList[i]).recharge();
        }
    }
}

/*!
        The player will launch an egg in the direction s/he currently is
*/
void Player::launch()
{
    if(this->isVisible())
    {
        int i = 0;
        bool launched = false;

        while((i<NO_OF_EGGS)&&(!launched))
        {
            if(!(*eggList[i]).isLaunched())
            {
                eggList[i]->launch(this->directionX);
                launched = true;
                eggs--;
            }
            i++;
        }
    }
}

//! Sets whether the player has reaches the end of the level.
void Player::setEnded(bool ended)
{
    this->ended = ended;
}

//! Checks if the player reached the end of the level.
bool Player::isEnded()
{
    return ended;
}

//! Adds points to the total amount of points hold by the player.
void Player::addPoints(int p)
{
    points += p;
}

//! Returns the score of the player.
int Player::getPoints()
{
    return points;
}

//! Returns the array of eggs associated to the player.
int Player::getEggs()
{
    return eggs;
}

//! Sets the array of eggs associated to the player.
void Player::setEggs(int n)
{
    eggs = n;
}

/*!
	The player will perform some other decisions about the movement
 */
void Player::move()
{
        if(isEnded())
            return;


	int isCollidingBottom = NOT_COLLIDING;
	int isCollidingFront = NOT_COLLIDING;
	int isCollidingTop = NOT_COLLIDING;

	int collisionIndex = 0;

	Character::move(isCollidingBottom, isCollidingFront, isCollidingTop, collisionIndex);


        if (!this->isImmortal && (isCollidingTop == DEATHLY_COLLIDING || (isCollidingFront == DEATHLY_COLLIDING && isCollidingBottom != DEATHLY_COLLIDING))){
            //this->setVisible(false);
            this->life--;
            /*if(life == 0){
                this->setVisible(false);
                return;
            }*/
            this->isImmortal = true;
            isImmortalThread->setTime(1);
            isImmortalThread->start();
            return;
        }

	//if the player is colliding with an enemy on the left
        if(isCollidingBottom == DEATHLY_COLLIDING){
                //level->getEnemies()->at(collisionIndex)->setVisible(false);
                level->getEnemies()->at(collisionIndex)->setLife(level->getEnemies()->at(collisionIndex)->getLife() -1);             
		jumping_force = PLAYER_Y_VELOCITY/2;
		return;
	}

	//if colliding with a collectable item collect it!!
	if (isCollidingBottom == COLLECTABLE_COLLIDING || isCollidingFront == COLLECTABLE_COLLIDING || isCollidingTop == COLLECTABLE_COLLIDING){
		level->getCollects()->at(collisionIndex)->setVisible(false);

                int value = level->getCollects()->at(collisionIndex)->getValue();

                if(value > 0)
                    points +=( level->getCollects()->at(collisionIndex)->getValue() );
                else
                {
                    rechargeEggs(value * -1);
                }
	}

        //if the end of the level is reached
        if(this->level->checkEnd(this->posX,this->posY))
        {
            //this->setVisible(false);
            this->setEnded(true);
            emit reachedEnd();
        }
}
