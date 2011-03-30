/*
 * TestPlayer.cpp
 *
 *  Created on: Apr 20, 2010
 *      Author: marco
 */

#include "TestPlayer.h"
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

void TestPlayer::testAdvance(){
	Level level;
//	the creation of the level is supposed to work"paintPlayer", ":/Characters/player.gif", *this);
	level.parseXML("test.xml");
        Player *actor = new Player(0, 0, 10, 10, level, NULL);

	actor->setVelocityX(PLAYER_X_VELOCITY);
	actor->move();
	QCOMPARE(actor->getX() , 2);

	delete actor;

}

void TestPlayer::testFall(){
	Level level;
	level.parseXML("test.xml");
        Player *actor = new Player(0, 0, 10, 10, level, NULL);

	actor->move();
	QCOMPARE(actor->getY() , 1);

	delete actor;
}

void TestPlayer::testJump(){
	Level level;
	level.parseXML("test.xml");
        Player *actor = new Player(100, 540, 10, 10, level, NULL);

	actor->setIsWillingToJump(true);
	int afterJump = actor->getY() + PLAYER_Y_VELOCITY+1;
	actor->move();

	QCOMPARE(actor->getY() , afterJump);

	afterJump += (PLAYER_Y_VELOCITY+1);
	actor->move();
	QCOMPARE(actor->getY() , afterJump);

	delete actor;
}

void TestPlayer::testCollectCoins(){

	Level level;
	level.parseXML("test.xml");

        Player *actor = new Player(598, 480, 10, 10, level, NULL);

	//right movement
	level.getCollects()->at(0)->setVisible(true);
	actor->setVelocityX(PLAYER_X_VELOCITY);
	actor->move();
	QCOMPARE(level.getCollects()->at(0)->isVisible() , false);
	delete actor;

	//falling
	level.getCollects()->at(0)->setVisible(true);
        actor = new Player(598, 479, 10, 10, level, NULL);
	actor->move();
	QCOMPARE(level.getCollects()->at(0)->isVisible() , false);
	delete actor;
}

void TestPlayer::testCollectEggs(){
        //qDebug() << "do not comment, implement";
        //QCOMPARE(true , false);

        Level level;
        level.parseXML("test.xml");

        Player *actor = new Player(598, 480, 10, 10, level, NULL);

        //right movement
        level.getCollects()->at(0)->setVisible(true);
        actor->setVelocityX(PLAYER_X_VELOCITY);
        actor->move();
        QCOMPARE(level.getCollects()->at(0)->isVisible() , false);
        delete actor;

        //falling
        level.getCollects()->at(0)->setVisible(true);
        actor = new Player(598, 479, 10, 10, level, NULL);
        actor->move();
        QCOMPARE(level.getCollects()->at(0)->isVisible() , false);
        delete actor;
}
void TestPlayer::testLaunchEggs(){
	Level level;
	level.parseXML("test.xml");

	Player *actor = new Player(598, 480, 10, 10, level, NULL);

//	actor->launch();

	int remainingEggs = actor->getEggs();

	QCOMPARE(NO_OF_EGGS-1, remainingEggs);

	for(int j = 0; j < NO_OF_EGGS-1; j++){
//		actor->launch();
	}

//	remainingEggs = actor->getEggs();

	QCOMPARE(0, remainingEggs);

}

void TestPlayer::testIncreaseScore(){

	Level level;
	level.parseXML("test.xml");

        Player *actor = new Player(658, 525, 10, 10, level, NULL);

	actor->setVelocityX(PLAYER_X_VELOCITY);
	actor->move();
	QCOMPARE(actor->getPoints(), 50);

	delete actor;

}

void TestPlayer::testKill(){

	Level level;
	level.parseXML("test.xml");

        Player *actor = new Player(800, 459, 10, 10, level, NULL);

        int tmpEnLife = level.getEnemies()->at(1)->getLife();
        int tmpPlLife = actor->getLife();

	actor->move();

        //check if enemy hit

        QCOMPARE(actor->getLife(), tmpPlLife);
        QCOMPARE(level.getEnemies()->at(1)->getLife(), tmpEnLife -1);

	delete actor;

        actor = new Player(802, 459, 10, 10, level, NULL);
        actor->move();
        level.getEnemies()->at(1)->move();

        //check if enemy killed

        QCOMPARE(actor->isVisible(), true);
        QCOMPARE(level.getEnemies()->at(1)->isVisible(), false);
}

void TestPlayer::testDie(){

	Level level;
	level.parseXML("test.xml");

        Player *actor = new Player(800, 470, 10, 10, level, NULL);
        actor->setVelocityX(PLAYER_X_VELOCITY);

        int tmpEnLife = level.getEnemies()->at(1)->getLife();
        int tmpPlLife = actor->getLife();

	actor->move();

        QCOMPARE(actor->getLife(), tmpPlLife -1);
        QCOMPARE(level.getEnemies()->at(1)->getLife(), tmpEnLife);

        delete actor;

        //check if player dead: i.e life = 0, visible = false

        actor = new Player(800, 470, 10, 10, level, NULL);
        actor->setLife(1);
        actor->setVelocityX(PLAYER_X_VELOCITY);
        actor->move();
        actor->move();

        QCOMPARE(actor->isVisible(), false);
        QCOMPARE(level.getEnemies()->at(1)->isVisible(), true);
}

void TestPlayer::testCrossInvisibleItem(){

	Level level;
	level.parseXML("test.xml");

        Player *actor = new Player(598, 480, 10, 10, level, NULL);
	actor->move();
	//an enemy is killed
	actor->move();
	QCOMPARE(actor->getX(), 598);
	QCOMPARE(actor->getY(), 482);

	delete actor;
}

void TestPlayer::testPassLevel(){
    Level level;
    level.parseXML("test.xml");

    Player *actor = new Player(1275, 310, 10, 10, level, NULL);
    actor->move();

    QCOMPARE(level.checkEnd(actor->getX(),actor->getY()),true);
}
