#ifndef CONNECTIONSENDER_H_
#define CONNECTIONSENDER_H_

#include <QObject>
#include <QtNetwork>

class Client;

class ConnectionSender : public QThread{
    Q_OBJECT
public:


	ConnectionSender(Client*);
	virtual ~ConnectionSender();
	int sendDatagram(int);


private:
	Client* client;
	QUdpSocket* udpSocket;
	void run();

};


#endif /* CONNECTIONSENDER_H_ */
