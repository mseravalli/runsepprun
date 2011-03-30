/*
 * TestEnemy.h
 *
 *  Created on: Apr 29, 2010
 *      Author: marco
 */

#ifndef TESTENEMY_H_
#define TESTENEMY_H_

#include <QtTest/QtTest>
#include <QObject>

class TestEnemy : public QObject {

	Q_OBJECT

private slots:
	void changeDirection();

};

#endif /* TESTENEMY_H_ */
