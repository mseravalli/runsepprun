#include "GraphicItem.h"
#include "../RunServerRun/Globals.h"
#include "images.h"
#include "GraphicsView.h"

//! A new graphic item is initialized
/*!
 * A new graphic item is initialized, the paint function to use is decided basing
 * on the type of object
 */
GraphicItem::GraphicItem(int x, int y, int h, int w, QString col, QString img, QString type, MainWindow* window, int texture_offset){

    this->x = x;
    this->y = y;
    this->h = h;
    this->w = w;

    visible = true;
    isImmortal = false;

    this->imageRenderer = NULL;
    this->imageSize = 0;
    this->texture_offset = texture_offset;

    time = 0;

    lastDirX = NO_DIRECTION;

    //the paint function will point to the correct paint method, which is defined
    //for every different kind of block
    if(type == "paintRect")
        this->paintFunction = &GraphicItem::paintRect;
    if(type == "paintPlayer")
        this->paintFunction = &GraphicItem::paintPlayer;
    if(type == "paintImage")
        this->paintFunction = &GraphicItem::paintImage;
    if(type == "paintSheep")
        this->paintFunction = &GraphicItem::paintSheep;


    if(type == "paintImage") {
        imageRenderer =  new QSvgRenderer(img.prepend(QString(LEVEL_DIR) + "/"));
        imageSize = imageRenderer->defaultSize().width();
    } else if(type == "paintRect") {
        this->color = QColor(col);
    }

        this->window = window;

    if(type != "paintPlayer" && type != "paintSheep")
        setCacheMode(QGraphicsItem::DeviceCoordinateCache);


}

/*!
 * The graphic item is deleted and all the pointers are deleted or set to null
 */
GraphicItem::~GraphicItem(){
    delete imageRenderer;
    imageRenderer = NULL;
    window = NULL;

    paintFunction = NULL;
}

/*!
  It returns the area on the screen that have to be readrawn when the item is moved inside the GraphicsScene.
*/
QRectF GraphicItem::boundingRect() const
{
    return QRectF(0, -texture_offset, w, h + texture_offset);
}

/*!
  It handles the visual style for the Block, Enemy and Player.
*/
void GraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    (this->*paintFunction)(painter);
}

/*!
  Moves and redravs the WorldElement represented by this class.
*/
void GraphicItem::advance(int){
    if(visible){
        if(isVisible()){
                setPos(x, y);
        }
        else{
            show();
        }
    }
    else{
        hide();
    }
}


/*!
 * It handles the visual style for the Block, Enemy and Player.
 */
void GraphicItem::paintRect(QPainter* painter){
    painter->fillRect(QRectF(0,0,w,h), color);
}

void GraphicItem::paintSheep(QPainter* painter) {
    //painter->fillRect(QRectF(0,0,w,h), color);

    if(directionX == (quint8)LEFT_DIRECTION){
        if(directionY == UP_DIRECTION){
            renderizeSheep(sheepl11, painter);
        }
        else if(directionY == (quint8)DOWN_DIRECTION){
            renderizeSheep(sheepl12, painter);
        }
        else{
            renderizeSheep(sheepl[(time%24)/4], painter);
            time++;
        }
    }
    else{
        if(directionY == UP_DIRECTION){
            renderizeSheep(sheepr11, painter);
        }
        else if(directionY == (quint8)DOWN_DIRECTION){
            renderizeSheep(sheepr12, painter);
        }
        else{
            renderizeSheep(sheepr[(time%24)/4], painter);
            time++;
        }
    }
}

void GraphicItem::paintPlayer(QPainter* painter){
    //painter->fillRect(QRectF(0,0,w,h), Qt::magenta);

    if(directionX == (quint8)LEFT_DIRECTION){
        if(directionY == UP_DIRECTION){
            renderizePlayer(pleft11, painter);
        }
        else if(directionY == (quint8)DOWN_DIRECTION){
            renderizePlayer(pleft12, painter);
        }
        else{
            renderizePlayer(pleft[(time%40)/5], painter);
            time++;
        }
        lastDirX = LEFT_DIRECTION;
    }
    else if(directionX == RIGHT_DIRECTION){
        if(directionY == UP_DIRECTION){
            renderizePlayer(pright11, painter);
        }
        else if(directionY == (quint8)DOWN_DIRECTION){
            renderizePlayer(pright12, painter);
        }
        else{
            renderizePlayer(pright[(time%40)/5], painter);
            time++;
        }
        lastDirX = RIGHT_DIRECTION;
    }
    else{
        if(lastDirX == LEFT_DIRECTION){
            if(directionY == UP_DIRECTION){
                renderizePlayer(pleft11, painter);
            }
            else if(directionY == (quint8)DOWN_DIRECTION){
                renderizePlayer(pleft12, painter);
            }
            else{
                renderizePlayer(pleft0, painter);
            }
        }
        else{
            if(directionY == UP_DIRECTION){
                renderizePlayer(pright11, painter);
            }
            else if(directionY == (quint8)DOWN_DIRECTION){
                renderizePlayer(pright12, painter);
            }
            else{
                renderizePlayer(pright0, painter);
            }
        }
    }
}

//mettere a posto usando un solo metodo per renderizzare pecore e player(usa texture offset...)
void GraphicItem::renderizePlayer(int img[], QPainter* painter){
    int k=0;
    for(int i=-10; i<49; i++){
        for(int j=-22; j<40; j++){
            if(img[k] == 255 && img[k+1] ==  0 && img[k+2] == 240){

            }
            else{
                painter->setPen(QColor(img[k],img[k+1], img[k+2]));
                painter->drawPoint(j,i);
            }

            k += 3;
        }
    }
}

void GraphicItem::renderizeSheep(int img[], QPainter* painter){
    int k=0;
    for(int i=-5; i<25; i++){
        for(int j=0; j<30; j++){
            if(img[k] == 255 && img[k+1] ==  0 && img[k+2] == 240){

            }
            else{
                painter->setPen(QColor(img[k],img[k+1], img[k+2]));
                painter->drawPoint(j,i);
            }

            k += 3;
        }
    }
}

void GraphicItem::paintImage(QPainter* painter){
    for(int i = 0; i < w; i += imageSize)
        imageRenderer->render(painter, QRectF( i, 0, imageSize + 1, h + 1) );
}

void GraphicItem::setDirectionX(int dx){
    directionX = dx;
}

void GraphicItem::setDirectionY(int dy){
    directionY = dy;
}

void GraphicItem::setNewX(int posX){
    this->x = posX;
}

void GraphicItem::setNewY(int posY){
    this->y = posY;
}

void GraphicItem::setId(int id){
    this->id = id;
}

int GraphicItem::getId(){
    return this->id;
}

void GraphicItem::setLife(int l){
	this->life = l;
}

void GraphicItem::setPoints(int p){
	this->points = p;
}

void GraphicItem::setEggs(int e){
	this->eggs = e;
}

bool GraphicItem::isVisible(){
	return this->visible;
}

void GraphicItem::setIsVisible(bool v){
	this->visible = v;
}

int GraphicItem::getX(){
	return this->x;
}

int GraphicItem::getLife(){
    return this->life;
}

int GraphicItem::getEggs(){
    return this->eggs;
}

int GraphicItem::getPoints(){
    return this->points;
}
