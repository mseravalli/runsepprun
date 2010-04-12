/* 
 * File:   Player.h
 * Author: marco
 *
 * Created on April 12, 2010, 3:19 PM
 */

#ifndef _PLAYER_H
#define	_PLAYER_H

#include "Character.h"


class Player : Character {
public:
    Player();
    Player(const Player& orig);
    virtual ~Player();

    void hit();
    void launch();

private:

};

#endif	/* _PLAYER_H */

