#ifndef GRAPHICITEM_H
#define GRAPHICITEM_H

#include <QtGui>
#include "WorldElement.h"

class GraphicItem : public QGraphicsItem
{
public:
    GraphicItem(WorldElement*, int, int);

    QRectF boundingRect() const;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

private:
    WorldElement* element;
    int w, h;
};
#endif
