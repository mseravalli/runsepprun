#include "Character.h"

Character::Character() {
}

Character::Character(int x, int y, int w, int h) {
	WorldElement::WorldElement(x, y, w, h);
}

void Character::move(int accX, int accY){
    if(accX > 0 && accY > 0)
        if(!Level::isColliding(*this, posX+accX, posY+accY)){
            posX = posX + accX;
            posY = posY + accY - 1;
        }
}


