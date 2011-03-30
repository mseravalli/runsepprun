/*
 * UDPSender.h
 *
 *  Created on: May 20, 2010
 *      Author: marco
 */

#ifndef UDPSENDER_H_
#define UDPSENDER_H_

#include <QtNetwork>
#include <QtGui>
#include "Client.h"

class UDPSender : public QThread{
public:

	static QMutex mutex;
	static QWaitCondition canSend;

	UDPSender(Client*);
	~UDPSender();

	void setRunning(bool);

private:

	Client* client;
	QUdpSocket* udpSocket;

	bool running;

	void run();
	void sendDatagram();

};

#endif /* UDPSENDER_H_ */
