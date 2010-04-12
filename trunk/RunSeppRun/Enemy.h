/* 
 * File:   Enemy.h
 * Author: marco
 *
 * Created on April 12, 2010, 3:20 PM
 */

#ifndef _ENEMY_H
#define	_ENEMY_H

#include "Character.h"


class Enemy : public Character {
public:
    Enemy();
    Enemy(const Enemy& orig);
    virtual ~Enemy();
private:

};

#endif	/* _ENEMY_H */

