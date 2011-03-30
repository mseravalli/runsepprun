/*
 * TestCharacter.h
 *
 *  Created on: Apr 20, 2010
 *      Author: marco
 */

#ifndef TESTCHARACTER_H_
#define TESTCHARACTER_H_

#include <QtTest/QtTest>
#include <QObject>

class TestPlayer: public QObject{

	Q_OBJECT

private slots:

	void testAdvance();
	void testFall();
	void testJump();
	void testCollectCoins();
	void testCollectEggs();
	void testIncreaseScore();
	void testKill();
	void testDie();
	void testCrossInvisibleItem();
	void testLaunchEggs();
        void testPassLevel();

};

#endif /* TESTCHARACTER_H_ */
