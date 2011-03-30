#include <QApplication>
#include "Server.h"
#include <cstdlib>

int main(int argc, char *argv[])
{
    int retV;
    int noPlayers;

    QApplication app(argc, argv);
    app.setApplicationName("RunServerRun");

    if(argc == 2 && atoi(argv[1]) != -1)
    {
        noPlayers = atoi(argv[1]);

        if(noPlayers > MAX_PLAYERS)
            noPlayers = MAX_PLAYERS;
    }
    else
        noPlayers = MAX_PLAYERS;

    Server * server = new Server(noPlayers);
    retV = server->start();

    if(retV != 0)
        return retV;

    retV = app.exec();
    delete server;

    return retV;
}
