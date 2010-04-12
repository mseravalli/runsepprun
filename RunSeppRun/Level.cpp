/* 
 * File:   Level.cpp
 * Author: korn
 * 
 * Created on 12 aprile 2010, 18.22
 */

#include "Level.h"

Level::Level() {
}

bool Level::isColliding(Character &actor , int newX, int newY){

    WorldElement e = WorldElement(50,50,50,50);

    int cornerX;
    int cornerY;

    //0 = TOP
    //1 = RIGHT
    //2 = BOTTOM
    //3 = LEFT

    //to apply to every object in the collections


    //if one of the corners is is colliding with another block

    

    //top left corner
    cornerX = newX;
    cornerY = newY;
    if (cornerX > e.getX() && cornerX < (e.getX() + e.getWidth())){
        if(cornerY > e.getY() && cornerY < (e.getY() + e.getHeight())){
            return true;
        }
    }
    
    //top right corner
    cornerX = newX + actor.getWidth();
    cornerY = newY;
    if (cornerX > e.getX() && cornerX < (e.getX() + e.getWidth())){
        if(cornerY > e.getY() && cornerY < (e.getY() + e.getHeight())){
            return true;
        }
    }


    //bottom left corner
    cornerX = newX;
    cornerY = newY + actor.getHeight();
    if (cornerX > e.getX() && cornerX < (e.getX() + e.getWidth())){
        if(cornerY > e.getY() && cornerY < (e.getY() + e.getHeight())){
            return true;
        }
    }


    //bottom right corner
    cornerX = newX + actor.getWidth();
    cornerY = newY + actor.getHeight();
    if (cornerX > e.getX() && cornerX < (e.getX() + e.getWidth())){
        if(cornerY > e.getY() && cornerY < (e.getY() + e.getHeight())){
            return true;
        }
    }

    return false;
}
