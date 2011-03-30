#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QtGui>
#include "MainWindow.h"
#include "GraphicsScene.h"
#include "GraphicLevel.h"

class GraphicsView : public QGraphicsView {

    Q_OBJECT

public:
    GraphicsView(MainWindow *window);
    ~GraphicsView();

    void loadLevel(QString);
    void unloadLevel();

    void resumeGame();

    bool isLeftKeyPressed();
    bool isRightKeyPressed();

    void setUserIndex(int);
    int getUserIndex();

    GraphicLevel* getGraphicLevel();

    QTimer *timer;

protected:
    void drawForeground(QPainter *, const QRectF&);

private slots:
    void scroll();

private:

    bool keyLeft;
    bool keyRight;
    bool keyJump;
    bool keyLaunch;

    GraphicsScene *actualScene;
    GraphicLevel *graphicLevel;
    MainWindow *window;

    QFont* font;

    void resizeEvent(QResizeEvent * event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    int userIndex;
};

#endif // GRAPHICSVIEW_H

