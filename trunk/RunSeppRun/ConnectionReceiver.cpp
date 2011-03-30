#include <QtNetwork>
#include <QtDebug>

#include "ConnectionReceiver.h"
#include "MainWindow.h"
#include "MainMenu.h"
#include "GraphicsView.h"
#include "GraphicLevel.h"
#include "../RunServerRun/Globals.h"


UDPReceiver::UDPReceiver(Client* c) {

        this->client = c;
        udpSocket = c->getSocket();

}
UDPReceiver::~UDPReceiver() {
    client = NULL;
}

void UDPReceiver::run(){
    while(true) {
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


void UDPReceiver::processData(QByteArray *datagram) {
    if(datagram->at(0) == ITEM_PACKET && client->isReady()){
            client->getMainWindow()->view->getGraphicLevel()->updateItems(datagram);
    }
}

