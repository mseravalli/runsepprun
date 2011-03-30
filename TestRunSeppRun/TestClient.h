/*
 * TestClfg sg gient.h
 *
 *  Created o sdg sdgn: May 11, 2010
 *      Author: marco
 */

#ifndef TESTCLIENT_H_
#define TESTCLIENT_H_

#include <QtTest/QtTest>
#include <QObject>

class TestClient : public QObject{

	Q_OBJECT

private slots:

	void testSendHelloPacket();
	void testSendAckPacket();
	void testSendAck2Packet();
	void testSendLevelIDPacket();
	void testSendReadyPacket();
	void testSendKeyInputPacket();


};

#endif /* TESTCLIENT_H_ */
