/*
 * TestClient.cpp
 *
 *  Created on: May 11, 2010
 *      Author: marco
 */

#include "TestClient.h"

class Client;
#include <QtGui>
#include <QUdpSocket>

#include "Client.h"
#include "../RunServerRun/Globals.h"






//QCOMPARE(level.isColliding(*actor, 0, 0, &index), NOT_COLLIDING);

void TestClient::testSendHelloPacket(){

	Client* client = new Client(NULL);

	QUdpSocket* socket = new QUdpSocket();
	socket->bind(INCOMING_PORT);

	client->sendDatagram(HELLO_PACKET);

	QHostAddress *address = NULL;
	quint16 *port = NULL;
	QByteArray *datagram = new QByteArray(socket->pendingDatagramSize(), (char) 0);

	socket->readDatagram(datagram->data(), datagram->size(), address, port);

	QCOMPARE(datagram->at(0), HELLO_PACKET);

	delete socket;

}


void TestClient::testSendAckPacket(){

	Client* client = new Client(NULL);

	QUdpSocket* socket = new QUdpSocket();
	socket->bind(INCOMING_PORT);

	client->sendDatagram(ACK_PACKET);

	QHostAddress *address = NULL;
	quint16 *port = NULL;
	QByteArray *datagram = new QByteArray(socket->pendingDatagramSize(), (char) 0);

	socket->readDatagram(datagram->data(), datagram->size(), address, port);

	QCOMPARE(datagram->at(0), ACK_PACKET);
	QCOMPARE((int)datagram->at(1), -1);

	delete socket;

}


void TestClient::testSendAck2Packet(){

	Client* client = new Client(NULL);

	QUdpSocket* socket = new QUdpSocket();
	socket->bind(INCOMING_PORT);

	client->sendDatagram(ACK2_PACKET);

	QHostAddress *address = NULL;
	quint16 *port = NULL;
	QByteArray *datagram = new QByteArray(socket->pendingDatagramSize(), (char) 0);

	socket->readDatagram(datagram->data(), datagram->size(), address, port);

	QCOMPARE(datagram->at(0), ACK2_PACKET);
	QCOMPARE((int)datagram->at(1), -1);

	delete socket;

}


void TestClient::testSendLevelIDPacket(){

	Client* client = new Client(NULL);

	QUdpSocket* socket = new QUdpSocket();
	socket->bind(INCOMING_PORT);

	client->setLevelID(1);
	client->sendDatagram(LEVEL_ID_PACKET);

	QHostAddress *address = NULL;
	quint16 *port = NULL;
	QByteArray *datagram = new QByteArray(socket->pendingDatagramSize(), (char) 0);

	socket->readDatagram(datagram->data(), datagram->size(), address, port);

	QCOMPARE(datagram->at(0), LEVEL_ID_PACKET);
	QCOMPARE((int)datagram->at(1), -1);
	QCOMPARE((int)datagram->at(2), 1);

	delete socket;

}


void TestClient::testSendReadyPacket(){

	Client* client = new Client(NULL);

	QUdpSocket* socket = new QUdpSocket();
	socket->bind(INCOMING_PORT);

	client->sendDatagram(READY_PACKET);

	QHostAddress *address = NULL;
	quint16 *port = NULL;
	QByteArray *datagram = new QByteArray(socket->pendingDatagramSize(), (char) 0);

	socket->readDatagram(datagram->data(), datagram->size(), address, port);

	QCOMPARE(datagram->at(0), READY_PACKET);
	QCOMPARE((int)datagram->at(1), -1);

	delete socket;

}


void TestClient::testSendKeyInputPacket(){
	Client* client = new Client(NULL);

	QUdpSocket* socket = new QUdpSocket();
	socket->bind(INCOMING_PORT);

	client->setDirection(1);
	client->setIsJumping(false);
	client->setIsLaunching(true);
	client->sendDatagram(KEY_INPUT_PACKET);

	QHostAddress *address = NULL;
	quint16 *port = NULL;
	QByteArray *datagram = new QByteArray(socket->pendingDatagramSize(), (char) 0);

	socket->readDatagram(datagram->data(), datagram->size(), address, port);

	QCOMPARE(datagram->at(0), KEY_INPUT_PACKET);
	QCOMPARE((int)datagram->at(1), -1);
	QCOMPARE((int)datagram->at(2), 1);
	QCOMPARE((bool)datagram->at(3), false);
	QCOMPARE((bool)datagram->at(4), true);

	delete socket;
}
