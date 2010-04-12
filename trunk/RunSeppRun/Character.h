/* 
 * File:   Character.h
 * Author: marco
 *
 * Created on April 12, 2010, 2:08 PM
 */

#ifndef _CHARACTER_H
#define	_CHARACTER_H

#include "WorldElement.h"


class Character : public WorldElement {
public:
    Character();
    Character(const Character& orig);
    virtual ~Character();
//    move will inlcude jump too
    virtual void move() = 0;
private:

    int life;

};

#endif	/* _CHARACTER_H */

