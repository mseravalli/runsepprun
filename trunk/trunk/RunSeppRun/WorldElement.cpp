#include "WorldElement.h"

WorldElement::WorldElement() {
}

WorldElement::WorldElement(int x, int y, int w, int h){
    this->posX = x;
    this->posY = y;
    this->width = w;
    this->height = h;
}

int WorldElement::getX() const{
    return this->posX;
}

int WorldElement::getY() const{
    return this->posY;
}

int WorldElement::getHeight() const{
    return this->height;
}

int WorldElement::getWidth() const{
    return this->width;
}
