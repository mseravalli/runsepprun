#ifndef GRAPHICLEVEL_H
#define GRAPHICLEVEL_H

#include "GraphicItem.h"

class GraphicLevel
{
public:
    GraphicLevel();
    ~GraphicLevel();

    QList<GraphicItem*> graphicWorld;
};

#endif
