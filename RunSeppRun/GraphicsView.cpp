#include "GraphicsView.h"

GraphicsView::GraphicsView(QWidget* parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0,0,800,600);

    setScene(scene);

    // Optimizations
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setOptimizationFlags( QGraphicsView::DontSavePainterState | QGraphicsView::DontAdjustForAntialiasing);

    // Timer
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(1000/80);
}

void GraphicsView::resizeEvent(QResizeEvent * event)
{
   QGraphicsView::resizeEvent(event);
   this->fitInView(scene->sceneRect(), Qt::IgnoreAspectRatio);
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Left:
            break;
        case Qt::Key_Right:
            break;
        case Qt::Key_Space:
            break;
        default:
            break;
    }
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Left:
            break;
        case Qt::Key_Right:
            break;
        case Qt::Key_Space:
            break;
        default:
            break;
    }
}
