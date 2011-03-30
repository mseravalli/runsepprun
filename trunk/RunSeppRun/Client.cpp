#include "Client.h"
#include <QtNetwork>
#include "../RunServerRun/Globals.h"
#include "../RunServerRun/Arch.h"
#include "GraphicsView.h"
#include "UDPReceiver.h"
#include "UDPSender.h"
#include "MainMenu.h"

//! Constructs a new Client initializing all the instance variables
Client::Client(MainWindow* window){
    this->window = window;

    receivedLvl = new QByteArray();

    this->clientAddress = new QHostAddress("127.0.0.1");
    this->serverAddress = new QHostAddress("127.0.0.1");
    serverPort = SERVER_INCOMING_PORT_TCP;

    tcpSocket = new QTcpSocket(window);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(startDialog()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
    		this, SLOT(errorHandler(QAbstractSocket::SocketError)) );
    connect(tcpSocket, SIGNAL(readyRead ()), this, SLOT(processDatagram()));
    udpSocket = new QUdpSocket();

    levelComplete = 0;
    levelSize = 0;

    id = -1;
    levelID = -1;

    this->playerDirX = 0;
    this->playerIsJumping = false;
    this->playerIsLaunching = false;

    ready = false;

    receiver = new UDPReceiver(this);
    sender = new UDPSender(this);

}

//! All the instance variables are deleted and set to NULL or to a default value
Client::~Client(){
    window = NULL;

    disconnectFromServer();

    delete sender;
    sender = NULL;

    delete receiver;
    receiver = NULL;

    delete udpSocket;
    udpSocket = NULL;

    delete tcpSocket;
    tcpSocket = NULL;

    delete clientAddress;
    clientAddress = NULL;

    delete serverAddress;
    serverAddress = NULL;

    delete receivedLvl;
    receivedLvl = NULL;

}


//! The disconnection from the server is performed: the sockets are closed and
void Client::disconnectFromServer(){

    delete receivedLvl;
    receivedLvl = new QByteArray();
    this->playerDirX = 0;
    this->playerIsJumping = false;
    this->playerIsLaunching = false;

    levelComplete = 0;
    levelSize = 0;

        ready = false;
        id = -1;
        levelID = -1;
        tcpSocket->disconnectFromHost();
        tcpSocket->close();

        sender->setRunning(false);
        receiver->setRunning(false);
        udpSocket->close();

}

//! The UDP socket is binded to a predefined port
int Client::bind() {
    if(!udpSocket->bind(CLIENT_INCOMING_PORT_UDP+id, QUdpSocket::DontShareAddress))
        return 1;
    return 0;
}

//! The server address and the server port are passed to the passed ones
void Client::setServerAddress(QString a, quint16 p){
        this->serverAddress = new QHostAddress(a);
        this->serverPort = p;
}

//! The client tries to connect to the set server
void Client::connectToServer(){
    tcpSocket->connectToHost(*serverAddress, serverPort);
}

//! The client slimply sends to the server a hello packet
void Client::startDialog(){
    levelComplete = 0;
    levelSize = 0;
    sendSetupPacket(HELLO_PACKET);
}

//! The client sends the correct packet type
/*!
 * For each type of packet a specific datagram is created:
 *
 * - HELLO_PACKET: 		position 0: type
 *
 * - ACK_PACKET:		position 0: type
 * 						position 1: client id
 *
 * - ACK2_PACKET:		position 0: type
 * 						position 1: client id
 *
 * - LEVEL_ID_PACKET:	position 0: type
 * 						position 1: client id
 * 						position 2: level id
 *
 * - READY_PACKET:		position 0: type
 * 						position 1: client id
 *
 * Afterwards the package is sent
 *
 */
int Client::sendSetupPacket(int type){
    QByteArray* message = new QByteArray(0, (char)0);

    switch (type){
    case HELLO_PACKET:
            message->insert(0, HELLO_PACKET);
            break;

    case ACK_PACKET:
            message->insert(0, ACK_PACKET);
            message->insert(1, id);
            break;

    case LEVEL_ID_PACKET:
            message->insert(0, LEVEL_ID_PACKET);
            message->insert(1, id);
            message->insert(2, levelID);
            break;

    case ACK2_PACKET:
            message->insert(0, ACK2_PACKET);
            message->insert(1, id);
            break;

    case READY_PACKET:
            ready = true;
            message->insert(0, READY_PACKET);
            message->insert(1, id);
            break;

    default : break;
    }

    if(message != NULL){
            tcpSocket->write(*message);
            tcpSocket->waitForBytesWritten(-1);
            tcpSocket->flush();
    } else {
            return 1;
    }
    delete message;
    return 0;
}

//! The data of the datagram is processed according to its type
/*!
 * Each type of datagram is processed in different ways:
 *
 * - ID_PACKET:			the client id and the client rights are updated
 *
 * - LEVELLIST_PACKET:	the datagram is translated into a QString and it is then
 *  					separated, afterwards a dialog box is shown to the player,
 *  					so that s/he can choose the correct level
 *
 * - LEVEL_PACKET:		the incoming packets are added to the instance datagram until
 * 						the total size of the level is downloaded, after that the
 * 						level is extracted and loaded in the graphics view, afterwards
 * 						the sender and the receiver are started and the ready packet
 * 						is sent
 *
 */
void Client::processData(QByteArray* datagram) {
    if(datagram->at(0) == ID_PACKET && datagram->size() == ID_PACKET_SIZE) {
        id = datagram->at(1);
        if(datagram->at(2) == ID_PACKET_RIGHTS_NEW){
                sendSetupPacket(ACK_PACKET);
        } else if (datagram->at(2) == ID_PACKET_RIGHTS_JOIN) {
                sendSetupPacket(ACK2_PACKET);
        }
        datagram->clear();
    }
    else if (datagram->at(0) == LEVELLIST_PACKET){
        QString inputLevels;

        for(int i = 2; i < datagram->size()-1; i++){
            inputLevels.append((unsigned char) datagram->at(i));
        }

        //the read string is split
        QStringList levelList = inputLevels.split(SEPARATOR);        

        bool ok;

        selectedLevel = QInputDialog::getItem(window, tr(" "), tr("<h4 align=\"center\">Choose Level</h4>"), levelList, 0, false, &ok);

        //if ok is pressed
        if(ok){
            levelID = levelList.indexOf(QRegExp(selectedLevel), 0);
            sendSetupPacket(LEVEL_ID_PACKET);
            sendSetupPacket(ACK2_PACKET);
        }
        //if cancel is pressed
        else{
            disconnectFromServer();
        }
        datagram->clear();
    }
    else if (datagram->at(0) == LEVEL_PACKET){
        int levelSize = ((unsigned char)datagram->at(1)*(256*256*256)) +
        		((unsigned char)datagram->at(2)*(256*256)) +
        		((unsigned char)datagram->at(3)*(256)) +
        		((unsigned char)datagram->at(4));
        if(datagram->size() == levelSize+5){

            QDir().mkdir(LEVEL_DIR);


            QDir dirLvl(LEVEL_DIR, "*", QDir::Name, QDir::Files);
            QStringList files = dirLvl.entryList();

            for(int i = 0; i < files.size(); i++)
            {
                dirLvl.remove(files[i]);
            }

            QFile out("levels/archive");
            if (!out.open(QIODevice::WriteOnly | QIODevice::Truncate)){
                qDebug() << "Could not write archive";
                return;
            }
            out.write(receivedLvl->right(levelSize));

            out.close();



            extract("levels/archive");

            dirLvl = QDir(LEVEL_DIR, "*.xml", QDir::Name, QDir::Files);
            files = dirLvl.entryList();

            QString fileName("");
            fileName.append(LEVEL_DIR);
            fileName.append("/");
            fileName.append(files.at(0));


            window->view->loadLevel( fileName);
            bind();
            receiver->start();
            sender->start();
            sendSetupPacket(READY_PACKET);

        }
    }
}


QUdpSocket* Client::getUDPSocket(){
    return this->udpSocket;
}

QHostAddress* Client::getServerAddress(){
	return this->serverAddress;
}

bool Client::isReady(){
    return this->ready;
}
MainWindow* Client::getWindow(){
    return window;
}

int Client::getDirection(){
	return this->playerDirX;
}

bool Client::isJumping(){
	return this->playerIsJumping;
}

bool Client::isLaunching(){
	return this->playerIsLaunching;
}

int Client::getID(){
	return this->id;
}

void Client::setLevelID(int i){
    levelID = i;
}

void Client::setDirection(int dir){
	this->playerDirX = dir;
}
void Client::setIsJumping(bool jump){
	this->playerIsJumping = jump;
}
void Client::setIsLaunching(bool launch){
	this->playerIsLaunching = launch;
}


//! The errors raised by the tcp socket are handled in this method
/*!
 * If the connection to the server is dropped an error dialog is shown to the player,
 * the current connection is closed and the main menu is displayed again
 */
void Client::errorHandler(QAbstractSocket::SocketError errorType){

	switch (errorType){
	case QAbstractSocket::ConnectionRefusedError:
		QMessageBox::about(window, "Connection failed",
				"The server may be not running or is busy at the moment.<br />"
				"Please try later.");
		window->view->unloadLevel();
		window->menu->openMainMenu();
		break;
	case QAbstractSocket::RemoteHostClosedError:

		this->disconnectFromServer();

		QMessageBox::about(window, "Connection failed",
				"The server may be not running or is busy at the moment.<br />"
				"Please try later.");
		window->view->unloadLevel();
		window->menu->openMainMenu();
		break;
	default:
                qDebug() << errorType;
		break;
	}
}

//! This slot is called whenever a package arrives to the tcp server
/*!
 * The data contained in the packets is read and put into the datagram and afterwards
 * is processed by the processData
 */
void Client::processDatagram(){

	QByteArray *datagram = new QByteArray();
	datagram->append(tcpSocket->read(1));

    if(datagram->at(0) == LEVEL_PACKET || levelComplete == -1){
        receivedLvl->append(datagram->at(0));
        if(receivedLvl->size() < 2){
            levelComplete = -1;
            receivedLvl->append(tcpSocket->read(4));
            levelSize = ((unsigned char)receivedLvl->at(1)*(256*256*256)) +
                        ((unsigned char)receivedLvl->at(2)*(256*256)) +
                        ((unsigned char)receivedLvl->at(3)*(256)) +
                        ((unsigned char)receivedLvl->at(4));
        }
        receivedLvl->append(tcpSocket->read(tcpSocket->bytesAvailable()));
        if(receivedLvl->size() == levelSize+5){
            levelComplete = 1;
        }
    }
    else if(datagram->at(0) == ID_PACKET && tcpSocket->bytesAvailable() == (ID_PACKET_SIZE - 1)){
        datagram->append(tcpSocket->read(ID_PACKET_SIZE - 1));
    }
    else if(datagram->at(0) == LEVELLIST_PACKET){
        datagram->append(tcpSocket->read(1));
        datagram->append(tcpSocket->read(datagram->at(1)));
    }
    else if(datagram->at(0) == END_PACKET && tcpSocket->bytesAvailable() == (END_PACKET_SIZE -1)){
        disconnectFromServer();
        window->view->unloadLevel();
        window->menu->openMainMenu();
    }
    else
    {
        qDebug() << "Early read or unknown packet.";

        delete datagram;

        disconnectFromServer();
        return;
    }
    if(!datagram->isEmpty()){
        if(datagram->size() > 1){
            processData(datagram);
        }
        else{
            if(levelComplete == 1 && !receivedLvl->isEmpty()){
                processData(receivedLvl);
                delete receivedLvl;
                receivedLvl = NULL;
            }
        }
    }
    else
    {
        qDebug() << "this point will never be reached";
    }


}
