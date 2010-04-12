/* 
 * File:   Character.h
 * Author: korn
 *
 * Created on 12 aprile 2010, 18.16
 */

#ifndef _CHARACTER_H
#define	_CHARACTER_H

#include "WorldElement.h"

class Character : public WorldElement {
public:
    Character();
    virtual void move();
protected:
    int life;

};

#endif	/* _CHARACTER_H */

