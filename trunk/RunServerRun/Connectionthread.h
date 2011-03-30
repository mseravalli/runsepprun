#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <QtCore>
#include <QtNetwork>

class Server;

//! Handles the connection to the client
/*!
        This thread handles the TCP connection with the client. It recieves the packets and sends the request for the setup of the connection.
 */
class ConnectionThread : public QThread
{

    Q_OBJECT

public:
    ConnectionThread(QTcpSocket *, Server *server);
    ~ConnectionThread();

    //void sendNextLevelPacket();


private slots:
    void cleanupAndTerminate();

public slots:
    void sendEndPacket();


signals:
    void startDataReceiver();

private:
    void run();
    void processData(QByteArray*, QList<QByteArray>*);

    QTcpSocket *socket;
    Server *server;

    //static QMutex mutex;
};

#endif
