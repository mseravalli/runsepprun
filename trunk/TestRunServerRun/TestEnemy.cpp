/*
 * TestEnemy.cpp
 *
 *  Created on: Apr 29, 2010
 *      Author: marco
 */

#include "TestEnemy.h"

#include "qdebug.h"
#include <QtGui>
#include "../RunServerRun/Level.h"
#include "../RunServerRun/WorldElement.h"
#include "../RunServerRun/Collect.h"
#include "../RunServerRun/Block.h"
#include "../RunServerRun/Character.h"
#include "../RunServerRun/Player.h"
#include "../RunServerRun/Enemy.h"
#include "../RunServerRun/Globals.h"
#include "../RunServerRun/Egg.h"
#include "../RunServerRun/BackgroundElement.h"

void TestEnemy::changeDirection(){

	Level level;
	level.parseXML("test.xml");
	Enemy *enemy = new Enemy(0, 0, 10, 10, LEFT_DIRECTION, level);

	QCOMPARE(enemy->getDirectionX() , LEFT_DIRECTION);
	enemy->move();
	QCOMPARE(enemy->getDirectionX() , RIGHT_DIRECTION);

	delete enemy;

}
