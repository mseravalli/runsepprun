#ifndef LEVEL_H
#define	LEVEL_H

class Character;
#include "Character.h"


class Level {
public:
    Level();
    static bool isColliding(const Character&, int, int);
private:

};

#endif
