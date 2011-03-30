#include "GraphicsView.h"
#include "../RunServerRun/Globals.h"
#include "MainMenu.h"
#include "UDPSender.h"
#include "Client.h"

/*!
  Creates a new instance of GraphicsView. It sets some optimizations for the rendering performance and sets the MainMenu.
*/
GraphicsView::GraphicsView(MainWindow * window){
    this->window = window;

    // Timer
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(scroll()));

    // Fonts
    font = new QFont("Helvetica", 15, QFont::Bold);

    graphicLevel = NULL;
    actualScene = NULL;

    userIndex = -1;

    // Rendering optimizations
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::NoViewportUpdate); // BoundingRect // Smart
    setOptimizationFlags( QGraphicsView::DontSavePainterState | QGraphicsView::DontAdjustForAntialiasing);
}

/*!
 * the pointers are deleted and set to null
 */
GraphicsView::~GraphicsView(){
    window = NULL;

    actualScene = NULL;
    graphicLevel = NULL;

    delete timer;
    timer = NULL;

    delete font;
    font = NULL;
}

/*!
 * the level is loaded from a given level path, firstly it is parsed and the grahpich
 * world is created afterwards the graphic level is imported in the graphic scene,
 * the parameters are set to the correct value, the graphics view is initialized
 * the focus is put on it
 */
void GraphicsView::loadLevel(QString levelPath){

    // a new level is created and it is initialized
    graphicLevel = new GraphicLevel(window);
    if( graphicLevel->parseLevel(levelPath) != LEVEL_LOADED){
        qDebug()<< "Could not parse level.";

        unloadLevel();
        return;

    }

    //Scene
    actualScene = new GraphicsScene();
    actualScene->parseGraphicLevel(graphicLevel);
    setScene(actualScene);

    keyLeft = false;
    keyRight = false;
    keyJump = false;
    keyLaunch = false;

    timer->start(TIMER_X_MSEC);

    window->menu->hide();
    window->view->show();
    window->setFocus();
    window->view->setFocus();

    setSceneRect(0, 0, BASE_X_RESOLUTION, BASE_Y_RESOLUTION);

}

/*!
 * the level is onloaded and the variables are freed
 */
void GraphicsView::unloadLevel(){

    timer->stop();

    this->hide();

    delete graphicLevel;
    graphicLevel = NULL;

    delete actualScene;
    actualScene = NULL;

}

void GraphicsView::scroll(){

	QRectF sceneRectangle = sceneRect();

        if(userIndex != -1){

            if(!graphicLevel->getGraphicWorld()->at(userIndex)->isVisible()){
                window->getClient()->disconnectFromServer();
                unloadLevel();
                window->menu->openMainMenu();
                return;
            }

            if(keyLeft){

                if(window->getClient()->getDirection() != LEFT_DIRECTION){
                        window->getClient()->setDirection(LEFT_DIRECTION);
                                UDPSender::canSend.wakeOne();
                }

                if(graphicLevel->getGraphicWorld()->at(userIndex)->getX() - sceneRectangle.x() <= CENAL_AREA_LEFT - PLAYER_WIDTH &&
                                sceneRectangle.x() > 0){
                        setSceneRect(sceneRectangle.x() - PLAYER_X_VELOCITY * 2, sceneRectangle.y() + 0, BASE_X_RESOLUTION, BASE_Y_RESOLUTION);
                }

            }
            else if (keyRight){
                if(window->getClient()->getDirection() != RIGHT_DIRECTION){
                        window->getClient()->setDirection(RIGHT_DIRECTION);
                                UDPSender::canSend.wakeOne();
                }

                if(graphicLevel->getGraphicWorld()->at(userIndex)->getX() - sceneRectangle.x() >= CENAL_AREA_RIGHT &&
                                sceneRectangle.x()  + BASE_X_RESOLUTION < graphicLevel->getLevelLength()){
                        setSceneRect(sceneRectangle.x() + PLAYER_X_VELOCITY * 2, sceneRectangle.y() + 0, BASE_X_RESOLUTION, BASE_Y_RESOLUTION);
                }

            }
            else if(!keyLeft && !keyRight){
                if(window->getClient()->getDirection() != 0){
                        window->getClient()->setDirection(NO_DIRECTION);
                                UDPSender::canSend.wakeOne();
                }
            }


            // JUMPING
            if(keyJump) {
                if(!window->getClient()->isJumping()){
                        window->getClient()->setIsJumping(keyJump);
                                UDPSender::canSend.wakeOne();
                }
            } else {
                if(window->getClient()->isJumping()){
                        window->getClient()->setIsJumping(keyJump);
                                UDPSender::canSend.wakeOne();
                }
            }


            // LAUNCH EGGS
            if(keyLaunch) {
                if(!window->getClient()->isLaunching()){
                        window->getClient()->setIsLaunching(keyLaunch);
                                UDPSender::canSend.wakeOne();
                }
                keyLaunch = false;
            }
        }






    actualScene->advance(); // Calls the advance() of all GraphicsItem into it

    // Repaint scene
    actualScene->update();
}

// Called on GraphicsView (consequently also an MainWindow) resize
void GraphicsView::resizeEvent(QResizeEvent * event)
{
    QGraphicsView::resizeEvent(event);

    if(actualScene != NULL)
        this->fitInView(actualScene->sceneRect(), Qt::IgnoreAspectRatio);
}

void GraphicsView::drawForeground(QPainter * painter, const QRectF&){
    painter->setPen(Qt::black);
    painter->setFont(*font);
    painter->drawText(sceneRect().x() + 40, 50, QString().setNum(graphicLevel->getGraphicWorld()->at(userIndex)->getPoints()).prepend("Points: "));
    painter->drawText(sceneRect().x() + 40, 100, QString().setNum(graphicLevel->getGraphicWorld()->at(userIndex)->getLife()).prepend("Life: "));
    painter->drawText(sceneRect().x() + BASE_X_RESOLUTION - 120, 50, QString().setNum(graphicLevel->getGraphicWorld()->at(userIndex)->getEggs()).prepend("Eggs: "));
}

GraphicLevel* GraphicsView::getGraphicLevel(){
    return this->graphicLevel;
}


void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Left:
            keyRight = false;
            keyLeft = true;
            break;
        case Qt::Key_Right:
            keyLeft = false;
            keyRight = true;
            break;
        case Qt::Key_Space:
            keyJump = true;
            break;
        case Qt::Key_Control:
            keyLaunch = true;
            break;
        case Qt::Key_Escape:
            window->view->hide();
            window->menu->openPauseMenu();
            timer->stop();
            break;
        default:
            break;
    }

}

void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Left:
            keyLeft = false;
            break;
        case Qt::Key_Right:
            keyRight = false;
            break;
        case Qt::Key_Space:
            keyJump = false;
            break;
        case Qt::Key_Control:
            keyLaunch = false;
            break;
        default:
            break;
    }

}

bool GraphicsView::isLeftKeyPressed(){
    return keyLeft;
}

bool GraphicsView::isRightKeyPressed(){
    return keyRight;
}

void GraphicsView::resumeGame(){
	this->show();
    window->setFocus();
    this->setFocus();
	timer->start(TIMER_X_MSEC);
}

void GraphicsView::setUserIndex(int index){
    this->userIndex = index;
}

int GraphicsView::getUserIndex(){
    return this->userIndex;
}
