#include "Enemy.h"
#include "Level.h"
#include "Character.h"
#include "WorldElement.h"
#include "Globals.h"

/*!
  Create a new Enemy by specifying its position, size, color and level in which it is contained.
*/
Enemy::Enemy(int x, int y, int w, int h, int initialDirection, Level* l) : Character(x, y, w, h, l)
{
    if(initialDirection == RIGHT_DIRECTION)
    	WorldElement::setVelocityX(ENEMY_X_VELOCITY);
    else if(initialDirection == LEFT_DIRECTION)
    	WorldElement::setVelocityX(-ENEMY_X_VELOCITY);
    else
        velocityX = 0;

    life = 1;

    jumpHeight = ENEMY_Y_VELOCITY;
}

//!  It moves the enemy.
/*!
  This method calculates and sets the position of the enemy during the movement.
  It makes sure that it changes direction when it collides with a WordElement.
*/
void Enemy::move()
{
    int isCollidingBottom = NOT_COLLIDING;
    int isCollidingFront = NOT_COLLIDING;
    int isCollidingTop = NOT_COLLIDING;

    int collisionIndex = 0;

    Character::move(isCollidingBottom, isCollidingFront,isCollidingTop, collisionIndex);

    if(isCollidingFront == ENVIRONMENT_COLLIDING || isCollidingFront == DEATHLY_COLLIDING || qrand()%TURN_RATE == 0)
    {
    	WorldElement::setVelocityX(-velocityX);
    }

    //the enemy will jump if it touches on the bottom either the floor or another enemy
    if((qrand()%JUMP_RATE == 0) && (isCollidingBottom == ENVIRONMENT_COLLIDING || isCollidingBottom == DEATHLY_COLLIDING))
    {
        setIsWillingToJump(true);
    }
}

