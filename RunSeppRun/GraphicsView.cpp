#include "GraphicsView.h"

#define BASE_X_RESOLUTION 800
#define BASE_Y_RESOLUTION 600
#define TIMER_X_SEC 80
#define SCENE_X_VELOCITY 2
#define SCENE_Y_VELOCITY 2

GraphicsView::GraphicsView(QWidget* parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0,0,BASE_X_RESOLUTION, BASE_Y_RESOLUTION);

    setScene(scene);

    // Optimizations
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setOptimizationFlags( QGraphicsView::DontSavePainterState | QGraphicsView::DontAdjustForAntialiasing);

    // Timer
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(scroll()));
    timer->start(1000/TIMER_X_SEC);
}

void GraphicsView::scroll()
{
    QRectF scene = sceneRect();
    setSceneRect(scene.x() + SCENE_X_VELOCITY, scene.y() + SCENE_Y_VELOCITY, BASE_X_RESOLUTION, BASE_Y_RESOLUTION);
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
