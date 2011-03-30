#include "UDPReceiver.h"
#include "../RunServerRun/Globals.h"
#include "GraphicsView.h"

UDPReceiver::UDPReceiver(Client* c){

	running = false;
    client = c;
    udpSocket = client->getUDPSocket();

}
UDPReceiver::~UDPReceiver(){

    udpSocket = NULL;
    client = NULL;
    running = false;

}

void UDPReceiver::run(){

	running = true;

    while(running) {
        msleep(10);
        if(udpSocket->hasPendingDatagrams()){
            QByteArray *datagram = new QByteArray(udpSocket->pendingDatagramSize(), (char) 0);

            if(udpSocket->readDatagram(datagram->data(), datagram->size(), NULL, NULL) != -1) {
                processData(datagram);
            }
            else {
                qDebug() << "Non dovrebbe mai succedere.";
            }
            delete datagram;
        }
    }

}


void UDPReceiver::setRunning(bool isRunning){
	this->running = isRunning;
	msleep(15);
	this->quit();
}

void UDPReceiver::processData(QByteArray *datagram) {
    if(datagram->at(0) == ITEM_PACKET && client->isReady()){
        client->getWindow()->view->getGraphicLevel()->updateItems(datagram);
    }
}

