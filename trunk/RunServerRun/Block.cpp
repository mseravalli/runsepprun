#include "Block.h"
#include <string>

/*!
  Create a new Block by specifying its position, level in which it is contained.
*/
Block::Block(int x, int y, int w, int h, Level* l) : WorldElement(x, y, w, h, l)
{
}
