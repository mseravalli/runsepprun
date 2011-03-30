#ifndef BACKGROUNDELEMENT_H
#define BACKGROUNDELEMENT_H

#include "WorldElement.h"

//! Element needed for the background only
/*!
	Element needed for the background only, the player will never collide with
	these kind of elements
 */
class BackgroundElement : public WorldElement
{
public:
    BackgroundElement(int, int, int, int, Level*);
};

#endif
