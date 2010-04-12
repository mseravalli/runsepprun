/* 
 * File:   Player.h
 * Author: korn
 *
 * Created on 12 aprile 2010, 18.19
 */

#ifndef _PLAYER_H
#define	_PLAYER_H

#include "Character.h"

class Player : public Character {
public:
    Player();
    void move(int, int);
    void hit();
    void launch();
private:

};

#endif	/* _PLAYER_H */

