/*
 * ConnectionSender.cpp
 *
 *  Created on: May 7, 2010
 *      Author: marco
 */

#include "ConnectionSender.h"
#include "Globals.h"
#include "Client.h"
#include <stdarg.h>



ConnectionSender::ConnectionSender(Client* c) {
	client = c;
	udpSocket = client->getSocket();

}

ConnectionSender::~ConnectionSender() {
	client = NULL;
	udpSocket = NULL;
}


void ConnectionSender::run(){

	while(true){
		client->canSend.wait(&client->mutex);
		sendDatagram(KEY_INPUT_PACKET);
		client->setIsLaunching(false);
	}
}




/*!
	sendDatagram simply sends datagrams to the address given by the instance variable
	client object, the method can send different kind of messages

	- HELLO_PACKET: 	it just contains the id of the packet

	- ACK_PACKET:		it contains at position 0 the packet's id, at position 1
						the client id

        - ACK2_PACKET:		it contains at position 0 the packet's id, at position 1
                                                the client id

	- LEVEL_ID_PACKET:	it stores at position 0 the packet's id, at position 1
						the client id and at position 2 the id of the level

	- READY_PACKET:		it stores at position 0 the packet's id, at position 1
						the client id

	- KEY_INPUT_PACKET:	it stores at position 0 the packet's id, at position 1
						the client id and at position 2 the dirX at position 3
						if the user wants to jump and at position 4 if the user
						wants to jump
 */
int ConnectionSender::sendDatagram(int type){

	QByteArray* message = new QByteArray(0, (char)0);

	switch (type){
	case HELLO_PACKET:
		message->insert(0, HELLO_PACKET);
		break;

	case ACK_PACKET:
		message->insert(0, ACK_PACKET);
		message->insert(1, client->getID());
		break;

	case LEVEL_ID_PACKET:
		message->insert(0, LEVEL_ID_PACKET);
		message->insert(1, client->getID());
		message->insert(2, client->getLevelID());
		break;

	case ACK2_PACKET:
		message->insert(0, ACK2_PACKET);
		message->insert(1, client->getID());
		break;

	case READY_PACKET:
		client->setIsReady(true);
		message->insert(0, READY_PACKET);
		message->insert(1, client->getID());
		break;

	case KEY_INPUT_PACKET:
		message->insert(0,KEY_INPUT_PACKET);
		message->insert(1,client->getID());

		message->insert(2,client->getDirection());
		message->insert(3,client->isJumping());
                message->insert(4,client->isLaunching());
		break;

	default : break;
	}



	if(message != NULL){
                udpSocket->writeDatagram(*message, *client->getServerAddress(), INCOMING_PORT);
	} else {
		return 1;
	}

	return 0;
}
