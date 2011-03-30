#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QtGui>
#include "GraphicLevel.h"


class GraphicsScene: public QGraphicsScene{

public:
    GraphicsScene();
    GraphicsScene(int, int, int, int);
    void parseGraphicLevel(GraphicLevel*);
};

#endif // GRAPHICSSCENE_H
