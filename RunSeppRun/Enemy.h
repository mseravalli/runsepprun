/* 
 * File:   Enemy.h
 * Author: korn
 *
 * Created on 12 aprile 2010, 18.20
 */

#ifndef _ENEMY_H
#define	_ENEMY_H

#include "Character.h"

class Enemy : public Character {
public:
    Enemy();
    void move(int, int);
private:

};

#endif	/* _ENEMY_H */

