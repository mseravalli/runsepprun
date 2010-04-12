/* 
 * File:   Level.h
 * Author: korn
 *
 * Created on 12 aprile 2010, 18.22
 */

#ifndef _LEVEL_H
#define	_LEVEL_H


#include "Character.h"

class Level {
public:
    Level();
     static bool isColliding(const Character&, int, int);
private:

};

#endif	/* _LEVEL_H */
