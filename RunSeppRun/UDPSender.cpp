/*
 * UDPSender.cpp
 *
 *  Created on: May 20, 2010
 *      Author: marco
 */

#include "UDPSender.h"
#include "../RunServerRun/Globals.h"

QMutex UDPSender::mutex;
QWaitCondition UDPSender::canSend;

UDPSender::UDPSender(Client* c) {

	this->client = c;
	this->udpSocket = client->getUDPSocket();
	running = false;

}

UDPSender::~UDPSender() {

	running = false;
	this->udpSocket = NULL;
	this->client = NULL;

}


void UDPSender::run(){

	running = true;

	while(running){
		sendDatagram();
		canSend.wait(&mutex);
	}

}

void UDPSender::sendDatagram(){

	QByteArray* message = new QByteArray(0, (char)0);

	message->insert(0,KEY_INPUT_PACKET);
	message->insert(1,client->getID());
	message->insert(2,client->getDirection());
	message->insert(3,client->isJumping());
	message->insert(4,client->isLaunching());


	udpSocket->writeDatagram(*message, *client->getServerAddress(), SERVER_INCOMING_PORT_UDP);

	client->setIsLaunching(false);

}

void UDPSender::setRunning(bool r){
	this->running = r;
	canSend.wakeAll();
	this->quit();
}
