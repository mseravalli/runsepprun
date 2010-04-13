#include "GraphicItem.h"

#define AA_BORDER 1

GraphicItem::GraphicItem(WorldElement* element, int w, int h)
{
    this->element = element;
    this->w = w;
    this->h = h;
}

QRectF GraphicItem::boundingRect() const
{
    return QRectF(-AA_BORDER, -AA_BORDER, w + AA_BORDER * 2, h + AA_BORDER * 2);
}

void GraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

}

