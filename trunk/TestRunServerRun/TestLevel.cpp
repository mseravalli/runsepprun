/*
 * TestLevel.cpp
 *
 *  Created on: Apr 20, 2010
 *      Author: marco
 */

#include "TestLevel.h"
#include "qdebug.h"
#include <QtGui>
#include <string>
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


/*!
 *	test for checking the correctness of the Level::isColliding method
 */
void TestLevel::testNoCollision(){

	Level level;
	level.parseXML("test.xml");

    Player *actor = new Player(0, 0, 10, 10, level, NULL);

    int index = -1;

    QCOMPARE(level.isColliding(*actor, 0, 0, &index), NOT_COLLIDING);

    delete actor;
    actor = NULL;

}

void TestLevel::testEnvironmentCollision(){

	Level level;
	level.parseXML("test.xml");

    Player *actor = new Player(0, 0, 10, 10, level, NULL);

    int index = -1;

    QCOMPARE(level.isColliding(*actor, 110, 540, &index), ENVIRONMENT_COLLIDING);

    delete actor;
    actor = NULL;

}

void TestLevel::testEnemyCollision(){

	Level level;
	level.parseXML("test.xml");

    Player *actor = new Player(0, 0, 10, 10, level, NULL);

    int index = -1;

    QCOMPARE(level.isColliding(*actor, 80, 12, &index), DEATHLY_COLLIDING);

    delete actor;
    actor = NULL;

}

void TestLevel::testCollectableCollision(){

	Level level;
	level.parseXML("test.xml");

    Player *actor = new Player(0, 0, 10, 10, level, NULL);

    int index = -1;

    QCOMPARE(level.isColliding(*actor, 680, 525, &index), COLLECTABLE_COLLIDING);

    delete actor;
    actor = NULL;

}

void TestLevel::testImmediateDeathCollision(){
	Level level;
	level.parseXML("test.xml");

    Player *actor = new Player(0, 0, 10, 10, level, NULL);

    int index = -1;

    QCOMPARE(level.isColliding(*actor, 850, 850, &index), IMMEDIATE_DEATH);

    delete actor;
    actor = NULL;
}

void TestLevel::parseXML(){

	Level level;
	level.parseXML("test.xml");

	QList<Block*> *environment = level.getEnvironment();
//	QList<Enemy*> *enemies = level.getEnemies();
	QList<Collect*> *collectItems = level.getCollects();

	QCOMPARE(environment->at(0)->getX(), 500);
	QCOMPARE(environment->at(0)->getY(), 500);
	QCOMPARE(environment->at(0)->getHeight(), 50);
	QCOMPARE(environment->at(0)->getWidth(), 20);

        QCOMPARE(collectItems->at(0)->getValue(), -3);

}

void TestLevel::loadLevel(){
	Level level;
	QCOMPARE(level.parseXML("test.xml"), 0);
}
