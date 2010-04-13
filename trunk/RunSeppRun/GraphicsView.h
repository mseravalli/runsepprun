#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QtGui>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QWidget* parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent * event);

private slots:
    void scroll();

private:
    QTimer *timer;
    QGraphicsScene *scene;

};

#endif