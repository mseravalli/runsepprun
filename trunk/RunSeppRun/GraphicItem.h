#ifndef GRAPHICITEM_H
#define GRAPHICITEM_H

#include "MainWindow.h"
#include <QtSvg>
#include <QtGui>


class GraphicItem : public QGraphicsItem{

public:
    GraphicItem(int, int, int, int, QString, QString, QString, MainWindow* window, int);
    ~GraphicItem();

    void paintRect(QPainter*);
    void paintPlayer(QPainter*);
    void paintImage(QPainter*);
    void paintSheep(QPainter*);

    QRectF boundingRect() const;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

    void setDirectionX(int);
    void setDirectionY(int);
    void setNewX(int);
    void setNewY(int);
    void setLife(int);
    void setPoints(int);
    void setEggs(int);

    bool isVisible();
    void setIsVisible(bool);

    void setId(int);
    int getId();

    int getX();

    int getPoints();
    int getLife();
    int getEggs();

protected:
        void advance(int);

private:

    int id;

    int x;
    int y;
    int w;
    int h;
    int directionX;
    int directionY;
    bool visible;
    bool isImmortal;

    int life;
    int points;
    int eggs;

    int time;

    int lastDirX;

    QColor color;

    MainWindow* window;

    QSvgRenderer* imageRenderer;
    int imageSize;
    int texture_offset;

    void (GraphicItem::*paintFunction)(QPainter*);
    void renderizePlayer(int[], QPainter*);
    void renderizeSheep(int[], QPainter*);

};

#endif // GRAPHICITEM_H
