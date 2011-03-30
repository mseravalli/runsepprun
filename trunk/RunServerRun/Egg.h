#ifndef EGG_H_
#define EGG_H_

#include "Level.h"
#include "Player.h"
#include "WorldElement.h"

//! An Egg is a special item that can be launched to kill or to weaken an enemy
class Egg: public WorldElement {
public:
        Egg(int, int, int, int, Player*, Level*);
	~Egg();
	void move();
	void launch(int);
	void recharge();
	bool isLaunched();
private:
	bool launched;
        Player* player;
	double currentForceY;
	int collisionIndex;

};

#endif
