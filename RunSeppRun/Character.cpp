/* 
 * File:   Character.cpp
 * Author: korn
 * 
 * Created on 12 aprile 2010, 18.16
 */

#include "Character.h"

Character::Character() {
}
void Character::move(int accX, int accY){
    if(accX > 0 && accY > 0)
        if(!Level.isColliding(this, posX+accX, posY+accY)){
            posX = posX + accX;
            posY = posY + accY - 1;
        }
}


