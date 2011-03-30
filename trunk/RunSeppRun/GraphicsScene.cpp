#include "GraphicsScene.h"
#include "../RunServerRun/Globals.h"


/*!
  Creates a new instance of GraphicsScene with some optimizations.
*/
GraphicsScene::GraphicsScene(){
    setItemIndexMethod(QGraphicsScene::BspTreeIndex);
    setSceneRect(0,0,BASE_X_RESOLUTION, BASE_Y_RESOLUTION);
}

/*!
  Creates a new instance of GraphicsScene with some optimizations and assigns to it the position and the size.
*/
GraphicsScene::GraphicsScene(int x, int y, int w, int h) : QGraphicsScene(x, y, w, h){
    setItemIndexMethod(QGraphicsScene::BspTreeIndex);
    setSceneRect(0,0,BASE_X_RESOLUTION, BASE_Y_RESOLUTION);
}

/*!
  Given a GraphicsLevel it constructs the scene.
*/
void GraphicsScene::parseGraphicLevel(GraphicLevel* gl){
    QList<GraphicItem*>* graphicWorld = gl->getGraphicWorld();
    for(int i = 0; i < graphicWorld->size(); i++){
        addItem(graphicWorld->at(i));
    }
}

