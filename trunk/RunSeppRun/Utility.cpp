#include "Utility.h"


bool utility::isColliding(GraphicsItem* i1, GraphicsItem* i2, int deltaX, int deltaY)
{
    int x1, x2, w1, w2, y1, y2, h1, h2;
    QRectF tmp;

    tmp = i1->collisionRect();
    x1 = i1->x() + tmp.x() + deltaX;
    w1 = tmp.width();

    tmp = i2->collisionRect();
    x2 = i2->x() + tmp.x();
    w2 = tmp.width();

    if((x1+w1) <= x2 || (x2+w2) <= x1)
        return false;
    else
    {
        tmp = i1->collisionRect();
        y1 = i1->y() + tmp.y() + deltaY;
        h1 = tmp.height();

        tmp = i2->collisionRect();
        y2 = i2->y() + tmp.y();
        h2 = tmp.height();

        if((y1+h1) <= y2 || (y2+h2) <= y1)
            return false;
        else
            return true;
    }
}
