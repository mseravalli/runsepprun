#include "Collect.h"
#include <string>

//! Constucts a new collectable item
Collect::Collect(int x, int y, int w, int h, int value, Level* l) : WorldElement(x, y, w, h, l)
{
    this->value = value;
}

//! Returns the amount of points that the player gets by collecting this item.
int Collect::getValue()
{
    return value;
}
