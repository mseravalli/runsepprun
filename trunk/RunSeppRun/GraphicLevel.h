#ifndef GRAPHICLEVEL_H
#define GRAPHICLEVEL_H

#include <QtGui>
#include <QtXml>
#include "MainWindow.h"
#include "GraphicItem.h"

class GraphicLevel {
public:
    GraphicLevel(MainWindow*);
    ~GraphicLevel();
    int parseLevel(QString&);

    QList<GraphicItem*>* getGraphicWorld();

    int checkCorrectness(QDomElement&);
    int loadWEType(QDomElement&, QString*, QString*);

    int getIndexPlayer();

    void updateItems(QByteArray*);

    int getLevelLength();

private:
    MainWindow *window;
    QList<GraphicItem*> graphicWorld;
    int numberOfBlocks;
    int levelLength;

    int indexBackground;
    int indexCollect;
    int indexEnemy; 
    int indexPlayer;
    int indexBlock;
    int indexEgg;

    void addPlayer();
    void removeAllPlayers();

    void addEgg();
    void removeEggs();

    int connectedPlayers;
    int currentEggs;

};

#endif // GRAPHICLEVEL_H
