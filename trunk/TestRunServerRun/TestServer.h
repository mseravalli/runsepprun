/*
 * TestServer.h
 *
 *  Created on: May 11, 2010
 *      Author: marco
 */

#ifndef TESTSERVER_H_
#define TESTSERVER_H_

#include <QtTest/QtTest>
#include <QObject>

class TestServer : public QObject{

	Q_OBJECT

private slots:

	void testSendIDPacket();

};

#endif /* TESTSERVER_H_ */
