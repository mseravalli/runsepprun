#ifndef COLLECT_H
#define COLLECT_H

#include "WorldElement.h"
#include <string>

//! Collectable objects
/*!
	 These kind of objects are scattered though the whole level and the player
	 can collect them, the collect can contain different kind of values
 */
class Collect : public WorldElement
{
public:
    Collect(int, int, int, int, int, Level*);
    int getValue();
private:
    int value;
};

#endif
