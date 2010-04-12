/* 
 * File:   WorldElement.cpp
 * Author: marco
 * 
 * Created on April 12, 2010, 6:02 PM
 */

#include "WorldElement.h"

WorldElement::WorldElement() {
}

int WorldElement::getX(){
    return this->posX;
}

int WorldElement::getY(){
    return this->posY;
}

int WorldElement::getHeight(){
    return this->height;
}

int WorldElement::getWidth(){
    return this->width;
}