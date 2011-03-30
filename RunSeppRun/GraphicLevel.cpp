#include "GraphicLevel.h"
#include "../RunServerRun/Globals.h"
#include "GraphicsView.h"
#include "Client.h"

/*!
  Creates an empty GraphicLevel.
*/
GraphicLevel::GraphicLevel(MainWindow * window){
    this->window = window;
    this->graphicWorld = QList<GraphicItem*>();

    indexBackground = -1;
    indexCollect = -1;
    indexEnemy = -1;
    indexPlayer = -1;
    indexBlock = -1;
    indexEgg = -1;

    numberOfBlocks = 0;

    connectedPlayers = 0;

    currentEggs = 0;

}

/*!
  Destroys an instance of GraphicLevel and all elements inside this collection.
*/
GraphicLevel::~GraphicLevel(){
    window = NULL;

    for(int i = 0; i < graphicWorld.size(); i++){
        delete graphicWorld[i];
        graphicWorld[i] = NULL;
    }

    graphicWorld.clear();

}

/*!
 * If some tags are not present in the .xml file an error code is returned
 */
int GraphicLevel::checkCorrectness(QDomElement& level){

    if (level.isNull())
        return NOT_WELL_FORMED;

    levelLength = level.attributes().namedItem("levelLength").nodeValue().toInt();
    if(levelLength <= BASE_X_RESOLUTION)
        return NOT_WELL_FORMED;

    QDomElement envElement;

    envElement = level.firstChildElement(QString("backgrounds"));
    if(envElement.isNull())
        return NOT_WELL_FORMED;

    envElement = level.firstChildElement(QString("environment"));
    if(envElement.isNull())
        return NOT_WELL_FORMED;

    envElement = level.firstChildElement(QString("enemies"));
    if(envElement.isNull())
        return NOT_WELL_FORMED;

    envElement = level.firstChildElement(QString("collects"));
    if(envElement.isNull())
        return NOT_WELL_FORMED;

    envElement = level.firstChildElement(QString("finalBlocks"));
    if(envElement.isNull())
        return NOT_WELL_FORMED;


    return 0;
}

/*!
 * A world element is loaded from the level
 */
int GraphicLevel::loadWEType(QDomElement& level, QString* category, QString* kind){

    QDomElement elementCollection = level.firstChildElement(*category);

    QDomElement element = elementCollection.firstChildElement(*kind);

    int x;
    int y;
    int w;
    int h;
    QString color = "";
    QString type;
    QString image = "";

    GraphicItem* tmpGI;

    while (!element.isNull()){
        if(*kind == "block"){
            numberOfBlocks++;            
        }

        if (!element.attributes().namedItem("type").nodeValue().isEmpty())
                type = element.attributes().namedItem("type").nodeValue();
        else
                return INCONSISTENT_VALUES;

        if (!element.attributes().namedItem("x").nodeValue().isEmpty())
                x = element.attributes().namedItem("x").nodeValue().toInt();
        else
                return INCONSISTENT_VALUES;

        if (!element.attributes().namedItem("y").nodeValue().isEmpty())
            y = element.attributes().namedItem("y").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;


        if (!element.attributes().namedItem("w").nodeValue().isEmpty())
            w = element.attributes().namedItem("w").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!element.attributes().namedItem("h").nodeValue().isEmpty())
            h = element.attributes().namedItem("h").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!element.attributes().namedItem("h").nodeValue().isEmpty())
            h = element.attributes().namedItem("h").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if(type == "paintImage")
        {
            if ( !element.attributes().namedItem("image").nodeValue().isEmpty() )
                image = element.attributes().namedItem("image").nodeValue();
            else
                return INCONSISTENT_VALUES;
        }
        else
        {
            if (!element.attributes().namedItem("color").nodeValue().isEmpty())
                color = element.attributes().namedItem("color").nodeValue();
            else
                return INCONSISTENT_VALUES;
        }

        tmpGI = new GraphicItem(x, y, h, w, color, image, type, window, TEXTURE_OFFSET);
        graphicWorld.append(tmpGI);

        element = element.nextSibling().toElement();

    }

    return 0;
}

/*!
  Given the Level path, it creates the GraphicItem elements for it and adds them to itself.
  the method will return different values if the level is loaded correctly or not:
  0 if the level is loaded correctly
  1 if the file is not found
  2 if some tag is missing
  4 if the values in the tags are not consistent or they are missing
*/
int GraphicLevel::parseLevel(QString& path){

    //open the document
    QDomDocument doc("level");
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return FILE_NOT_FOUND;
    if (!doc.setContent(&file)) {
        file.close();
        return FILE_NOT_FOUND;
    }
    file.close();


    QDomElement level = doc.firstChildElement(QString("level"));       

    int returnedValue = 0;

    //check correctness of the level
    returnedValue = checkCorrectness(level);
    if(returnedValue != 0){
        return returnedValue;
    }

    //load the elements in the file

    indexBackground = graphicWorld.size();

    returnedValue = loadWEType(level, new QString("backgrounds"), new QString("background"));
    if(returnedValue != 0){
        return returnedValue;
    }

    returnedValue = loadWEType(level, new QString("finalBlocks"), new QString("finalBlock"));
    if(returnedValue != 0){
        return returnedValue;
    }

    indexCollect = graphicWorld.size();

    returnedValue = loadWEType(level, new QString("collects"), new QString("collect"));
    if(returnedValue != 0){
        return returnedValue;
    }

    indexEnemy = graphicWorld.size();

    returnedValue = loadWEType(level, new QString("enemies"), new QString("enemy"));
    if(returnedValue != 0){
        return returnedValue;
    }

    indexPlayer = graphicWorld.size();

    addPlayer();

    indexBlock = graphicWorld.size();

    returnedValue = loadWEType(level, new QString("environment"), new QString("block"));
    if(returnedValue != 0){
        return returnedValue;
    }

    indexEgg = graphicWorld.size();
    this->addEgg();

    return 0;
}


QList<GraphicItem*>* GraphicLevel::getGraphicWorld(){
    return &graphicWorld;
}

/*!
 * The items in the graphic world are updated accordingly to the received packets
 */
void GraphicLevel::updateItems(QByteArray* datagram){    
    int shift = 1;
    int j = 0;
    int infoDistance = 0;
    int numberOfEnemies = 0;
    int numberOfPlayers = 0;
    int numberOfEggs = 0;
    int numberOfCollectables = 0;


    //PROCESS ENEMIES
    if(datagram->size() > shift && numberOfBlocks > 0){
        numberOfEnemies = (unsigned char)datagram->at(shift);
        infoDistance = 8;        

        for(int i=0; i<numberOfEnemies; i++){
            j=2;

            int newX = (((unsigned char)datagram->at(i*infoDistance+shift+(j++)))*256)
                            +((unsigned char)datagram->at(i*infoDistance+shift+(j++)));
            int newY = (((unsigned char)datagram->at(i*infoDistance+shift+(j++)))*256)
                            +((unsigned char)datagram->at(i*infoDistance+shift+(j++)));
            int newDirX = (unsigned char)datagram->at(i*infoDistance+shift+(j++));
            int newDirY = (unsigned char)datagram->at(i*infoDistance+shift+(j++));

            graphicWorld.at(indexEnemy + i)->setNewX(newX);
            graphicWorld.at(indexEnemy + i)->setNewY(newY);
            graphicWorld.at(indexEnemy + i)->setDirectionX(newDirX);
            graphicWorld.at(indexEnemy + i)->setDirectionY(newDirY);           

            //if it is invisible and it wants to be visible

            char visibility = ((unsigned char)datagram->at(i*infoDistance+shift+(j++))) ;

            if( visibility == '\1' && !graphicWorld.at(indexEnemy + i)->isVisible()) {
                graphicWorld.at(indexEnemy+i)->setIsVisible(true);
            }
            //if it is visible and it wants to be invisible
            else if (visibility == '\0' && graphicWorld.at(indexEnemy + i)->isVisible()) {
                graphicWorld.at(indexEnemy+i)->setIsVisible(false);
            }
        }
        shift += 1 + numberOfEnemies*infoDistance;
    }
    else {
        return;
    }

    //PROCESS PLAYERS
    if(datagram->size() > shift && numberOfBlocks > 0){
        infoDistance = 12;
        numberOfPlayers = (unsigned char)datagram->at(shift);
        // if a player is deleted all players are deleted too and then readded

        if(numberOfPlayers != connectedPlayers){
            this->removeAllPlayers();
        }

        for(int i=0; i<numberOfPlayers; i++){
            j=1;

            int playerID = (unsigned char)datagram->at(i*infoDistance+(j++)+shift);
            int newX = (((unsigned char)datagram->at(i*infoDistance+(j++)+shift))*256)
                            +((unsigned char)datagram->at(i*infoDistance+(j++)+shift));
            int newY = (((unsigned char)datagram->at(i*infoDistance+(j++)+shift))*256)
                            +((unsigned char)datagram->at(i*infoDistance+(j++)+shift));

            if(newY > 1000){
                newY -= 1000;
                newY *= -1;
            }

            int newDirX = (unsigned char)datagram->at(i*infoDistance+(j++)+shift);
            int newDirY = (unsigned char)datagram->at(i*infoDistance+(j++)+shift);
            int life = (unsigned char)datagram->at(i*infoDistance+(j++)+shift);
            int points = (((unsigned char)datagram->at(i*infoDistance+(j++)+shift))*256)
                            +((unsigned char)datagram->at(i*infoDistance+(j++)+shift));
            int eggs = (unsigned char)datagram->at(i*infoDistance+(j++)+shift);            

            if(numberOfPlayers > connectedPlayers){
                connectedPlayers++;
                graphicWorld.at(indexPlayer + i)->setId(playerID);
                if(playerID == window->getClient()->getID()){
                    window->view->setUserIndex(indexPlayer + i);
                }
                graphicWorld.at(indexPlayer + i)->setIsVisible(true);
                graphicWorld.at(indexPlayer + i)->show();
            }


            graphicWorld.at(indexPlayer + i)->setNewX(newX);
            graphicWorld.at(indexPlayer + i)->setNewY(newY);
            graphicWorld.at(indexPlayer + i)->setDirectionX(newDirX);
            graphicWorld.at(indexPlayer + i)->setDirectionY(newDirY);
            graphicWorld.at(indexPlayer + i)->setLife(life);
            graphicWorld.at(indexPlayer + i)->setPoints(points);
            graphicWorld.at(indexPlayer + i)->setEggs(eggs);

            //if it is invisible and it wants to be visible

            char visibility = ((unsigned char)datagram->at(i*infoDistance+(j++)+shift)) ;

            if( visibility == '\1' && !graphicWorld.at(indexPlayer + i)->isVisible()) {
                graphicWorld.at(indexPlayer+i)->setIsVisible(true);
            }
            //if it is visible and it wants to be invisible
            else if (visibility == '\0' && graphicWorld.at(indexPlayer + i)->isVisible()) {
                graphicWorld.at(indexPlayer+i)->setIsVisible(false);
            }
        }
        shift += 1 + numberOfPlayers*infoDistance;
    }

    //PROCESS EGGS

    if(datagram->size() > shift && numberOfPlayers > 0){        
        numberOfEggs = (unsigned char)datagram->at(shift);
        infoDistance = 5;

        if(currentEggs != numberOfEggs){
            removeEggs();
        }

        for(int i=0; i < numberOfEggs; i++){
            j=1;
            int newX = (((unsigned char)datagram->at(i*infoDistance+(j++)+shift))*256)
                            +((unsigned char)datagram->at(i*infoDistance+(j++)+shift));
            int newY = (((unsigned char)datagram->at(i*infoDistance+(j++)+shift))*256)
                            +((unsigned char)datagram->at(i*infoDistance+(j++)+shift));

            //updateEggs
            if(currentEggs < numberOfEggs){
            	graphicWorld.at(indexEgg + i)->setVisible(true);
            	currentEggs++;
            }

            graphicWorld.at(indexEgg + i)->setNewX(newX);
            graphicWorld.at(indexEgg + i)->setNewY(newY);

            //if it is invisible and it wants to be visible

            char visibility = ((unsigned char)datagram->at(i*infoDistance+(j++)+shift)) ;

            if( visibility == '\1' && !graphicWorld.at(indexEgg + i)->isVisible()) {
                graphicWorld.at(indexEgg+i)->setIsVisible(true);
            }
            //if it is visible and it wants to be invisible
            else if (visibility == '\0' && graphicWorld.at(indexEgg + i)->isVisible()) {
                graphicWorld.at(indexEgg+i)->setIsVisible(false);
            }
        }
        shift += 1 + numberOfEggs*infoDistance;
    }


    //PROCESS COLLECTABLES
    if(datagram->size() > shift && numberOfPlayers > 0){
        numberOfCollectables = (unsigned char)datagram->at(shift);
        for(int i=1; i<=numberOfCollectables; i++){
            char visibility = ((unsigned char)datagram->at(i+shift));

            if(visibility == '\1' && !graphicWorld.at(indexCollect+i-1)->isVisible()) {
                graphicWorld.at(indexCollect+i-1)->setIsVisible(true);
            }
            //if it is visible and it wants to be invisible
            else if (visibility == '\0' && graphicWorld.at(indexCollect+i-1)->isVisible()) {
                graphicWorld.at(indexCollect+i-1)->setIsVisible(false);
            }
        }
    }
}

/*!
 * Adds a player and stores its index
 */
void GraphicLevel::addPlayer(){
    for(int i=0; i<MAX_PLAYERS; i++){
        GraphicItem* player = new GraphicItem(PLAYER_X, PLAYER_Y, PLAYER_HEIGHT, PLAYER_WIDTH, QString("green"), QString("player.gif"),
                QString("paintPlayer"), window, 0);
        graphicWorld.append(player);
        player->setIsVisible(false);        
    }
}

void GraphicLevel::addEgg(){

    for(int i = 0; i < NO_OF_EGGS * MAX_PLAYERS; i++){
        GraphicItem* egg = new GraphicItem(0, 0, EGG_SIZE, EGG_SIZE, EGG_COLOR, QString("egg.svg"),
                     QString("paintImage"), window, 0);
        egg->setVisible(false);
        graphicWorld.append(egg);
    }

}

/*!
 * Deletes all players
 */
void GraphicLevel::removeAllPlayers(){

    for(int i = 0; i < MAX_PLAYERS; i++){
        //graphicWorld.at(indexPlayer)->hide();
        graphicWorld.at(indexPlayer+i)->setIsVisible(false);
    }
    connectedPlayers = 0;

}

void GraphicLevel::removeEggs(){
    for(int i=0; i < NO_OF_EGGS * MAX_PLAYERS; i++){
        graphicWorld.at(indexEgg+i)->setIsVisible(false);
        currentEggs = 0;
    }
}

int GraphicLevel::getIndexPlayer(){
	return this->indexPlayer;
}

int GraphicLevel::getLevelLength(){
    return this->levelLength;
}
