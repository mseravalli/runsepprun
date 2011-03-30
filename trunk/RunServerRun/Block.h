#ifndef BLOCK_H
#define	BLOCK_H

#include "WorldElement.h"
#include <string>

//!  Level plattforms.
/*!
  This class represents the physical, fixed elements of the level .
*/
class Block : public WorldElement
{
public:
    Block(int, int, int, int, Level*);
private:

};

#endif

