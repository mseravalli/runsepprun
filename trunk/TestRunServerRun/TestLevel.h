/*
 * TestLevel.h
 *
 *  Created on: Apr 20, 2010
 *      Author: marco
 */

#ifndef TESTLEVEL_H_
#define TESTLEVEL_H_

#include <QtTest/QtTest>
#include <QObject>

class TestLevel : public QObject {

	Q_OBJECT

private slots:

	void loadLevel();
	void parseXML();
	void testNoCollision();
	void testEnvironmentCollision();
	void testEnemyCollision();
	void testCollectableCollision();
	void testImmediateDeathCollision();

};

#endif /* TESTLEVEL_H_ */
