#include "Level.h"
#include "Globals.h"
#include "Character.h"
#include "Enemy.h"
#include "Block.h"
#include <QtXml>
#include <QtGui>
#include <QtDebug>
#include <string>
#include "Collect.h"
#include "BackgroundElement.h"

/*!
  It generates the content of a Level instance by parsing xml level files.
*/
int Level::parseXML(std::string path)
{

    /*
      POSSIBLE ERRORS:
		see globals
    */

    QDomDocument doc("level");
    QFile file(QString(path.c_str()));

    if (!file.open(QIODevice::ReadOnly))
        return FILE_NOT_FOUND;
    if (!doc.setContent(&file))
    {
        file.close();
        return FILE_NOT_FOUND;
    }
    file.close();

    QDomElement level = doc.firstChildElement(QString("level"));
    if (level.isNull())
        return NOT_WELL_FORMED;

    levelLength = level.attributes().namedItem("levelLength").nodeValue().toInt();
    if(levelLength <= BASE_X_RESOLUTION)
        return NOT_WELL_FORMED;


    // creating the collections of blocks
    QDomElement envElement = level.firstChildElement(QString("environment"));
    if(envElement.isNull())
        return NOT_WELL_FORMED;

    QDomElement block = envElement.firstChildElement(QString("block"));


    int x;
    int y;
    int w;
    int h;
    std::string type;

    while (!block.isNull())
    {

        if (!block.attributes().namedItem("type").nodeValue().isEmpty())
            type = block.attributes().namedItem("type").nodeValue().toStdString();
        else
            return INCONSISTENT_VALUES;

        if (!block.attributes().namedItem("x").nodeValue().isEmpty())
            x = block.attributes().namedItem("x").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!block.attributes().namedItem("y").nodeValue().isEmpty())
            y = block.attributes().namedItem("y").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;


        if (!block.attributes().namedItem("w").nodeValue().isEmpty())
            w = block.attributes().namedItem("w").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!block.attributes().namedItem("h").nodeValue().isEmpty())
            h = block.attributes().namedItem("h").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!block.attributes().namedItem("h").nodeValue().isEmpty())
            h = block.attributes().namedItem("h").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if(type == "paintImage")
        {
            if (block.attributes().namedItem("image").nodeValue().isEmpty() )
                return INCONSISTENT_VALUES;
        }
        else
        {
            if (block.attributes().namedItem("color").nodeValue().isEmpty())
                return INCONSISTENT_VALUES;
        }

        this->environment.append(new Block(x, y, w, h, this));

        block = block.nextSibling().toElement();
    }

    //Creating the collection of enemies

    QDomElement inhabitantElement = level.firstChildElement(QString("enemies"));
    if(inhabitantElement.isNull())
        return NOT_WELL_FORMED;

    QDomElement enemy = inhabitantElement.firstChildElement(QString("enemy"));

    std::string start;

    while (!enemy.isNull())
    {

        if (!enemy.attributes().namedItem("type").nodeValue().isEmpty())
            type = enemy.attributes().namedItem("type").nodeValue().toStdString();
        else
            return INCONSISTENT_VALUES;

        if (!enemy.attributes().namedItem("x").nodeValue().isEmpty())
            x = enemy.attributes().namedItem("x").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!enemy.attributes().namedItem("y").nodeValue().isEmpty())
            y = enemy.attributes().namedItem("y").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!enemy.attributes().namedItem("w").nodeValue().isEmpty())
            w = enemy.attributes().namedItem("w").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!enemy.attributes().namedItem("h").nodeValue().isEmpty())
            h = enemy.attributes().namedItem("h").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!enemy.attributes().namedItem("start").nodeValue().isEmpty())
            start = enemy.attributes().namedItem("start").nodeValue().toStdString();
        else
            return INCONSISTENT_VALUES;

        if(type == "paintImage")
        {
            if (enemy.attributes().namedItem("image").nodeValue().isEmpty())
                return INCONSISTENT_VALUES;
        }
        else
        {
            if (enemy.attributes().namedItem("color").nodeValue().isEmpty())
                return INCONSISTENT_VALUES;
        }

        int initialDirection = 0;

        if(start == "left")
            initialDirection = LEFT_DIRECTION;
        else if(start == "right")
            initialDirection = RIGHT_DIRECTION;

        this->enemies.append(new Enemy(x, y, w, h, initialDirection, this));

        enemy = enemy.nextSibling().toElement();
    }

    //Creating the collection of collects

    QDomElement collectElement = level.firstChildElement(QString("collects"));
    if(collectElement.isNull())
        return NOT_WELL_FORMED;

    QDomElement collect = collectElement.firstChildElement(QString("collect"));

    int value;

    while (!collect.isNull())
    {

        if (!collect.attributes().namedItem("type").nodeValue().isEmpty())
            type = collect.attributes().namedItem("type").nodeValue().toStdString();
        else
            return INCONSISTENT_VALUES;

        if (!collect.attributes().namedItem("x").nodeValue().isEmpty())
            x = collect.attributes().namedItem("x").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!collect.attributes().namedItem("y").nodeValue().isEmpty())
            y = collect.attributes().namedItem("y").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!collect.attributes().namedItem("w").nodeValue().isEmpty())
            w = collect.attributes().namedItem("w").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!collect.attributes().namedItem("h").nodeValue().isEmpty())
            h = collect.attributes().namedItem("h").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!collect.attributes().namedItem("value").nodeValue().isEmpty())
            value = collect.attributes().namedItem("value").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if(type == "paintImage")
        {
            if (collect.attributes().namedItem("image").nodeValue().isEmpty())
                return INCONSISTENT_VALUES;
        }
        else
        {
            if (collect.attributes().namedItem("color").nodeValue().isEmpty())
                return INCONSISTENT_VALUES;
        }

        this->collects.append(new Collect(x, y, w, h, value, this));

        collect = collect.nextSibling().toElement();

    }

    //Creating the collection of backgrounds

    QDomElement bgElement = level.firstChildElement(QString("backgrounds"));
    if(bgElement.isNull())
        return NOT_WELL_FORMED;

    QDomElement bg = bgElement.firstChildElement(QString("background"));

    while (!bg.isNull())
    {

        if (!bg.attributes().namedItem("type").nodeValue().isEmpty())
            type = bg.attributes().namedItem("type").nodeValue().toStdString();
        else
            return INCONSISTENT_VALUES;

        if (!bg.attributes().namedItem("x").nodeValue().isEmpty())
            x = bg.attributes().namedItem("x").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!bg.attributes().namedItem("y").nodeValue().isEmpty())
            y = bg.attributes().namedItem("y").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!bg.attributes().namedItem("w").nodeValue().isEmpty())
            w = bg.attributes().namedItem("w").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!bg.attributes().namedItem("h").nodeValue().isEmpty())
            h = bg.attributes().namedItem("h").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if(type == "paintImage")
        {
            if (bg.attributes().namedItem("image").nodeValue().isEmpty())
                return INCONSISTENT_VALUES;
        }
        else
        {
            if (bg.attributes().namedItem("color").nodeValue().isEmpty())
                return INCONSISTENT_VALUES;
        }

        this->backgroundElements.append(new BackgroundElement(x, y, w, h, this));

        bg = bg.nextSibling().toElement();

    }

    //Creating the final block (traguardo)

    QDomElement fBlocks = level.firstChildElement(QString("finalBlocks"));

    if(fBlocks.isNull())
        return NOT_WELL_FORMED;

    QDomElement fb = fBlocks.firstChildElement(QString("finalBlock"));

    while (!fb.isNull())
    {

        if (!fb.attributes().namedItem("type").nodeValue().isEmpty())
            type = fb.attributes().namedItem("type").nodeValue().toStdString();
        else
            return INCONSISTENT_VALUES;

        if (!fb.attributes().namedItem("x").nodeValue().isEmpty())
            x = fb.attributes().namedItem("x").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!fb.attributes().namedItem("y").nodeValue().isEmpty())
            y = fb.attributes().namedItem("y").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!fb.attributes().namedItem("w").nodeValue().isEmpty())
            w = fb.attributes().namedItem("w").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if (!fb.attributes().namedItem("h").nodeValue().isEmpty())
            h = fb.attributes().namedItem("h").nodeValue().toInt();
        else
            return INCONSISTENT_VALUES;

        if(type == "paintImage")
        {
            if (fb.attributes().namedItem("image").nodeValue().isEmpty())
                return INCONSISTENT_VALUES;
        }
        else
        {
            if (fb.attributes().namedItem("color").nodeValue().isEmpty())
                return INCONSISTENT_VALUES;
        }

        this->finalBlocks.append( new Block(x, y, w, h, this) );

        fb = fb.nextSibling().toElement();
    }

    return LEVEL_LOADED;
}


/*!
  Checks the integrity of the xml file
*/

int Level::checkXML(std::string path)
{
    /*
      POSSIBLE ERRORS:
                see globals
    */

    QDomDocument doc("level");
    QFile file(QString(path.c_str()));

    if (!file.open(QIODevice::ReadOnly)) return FILE_NOT_FOUND;
    if (!doc.setContent(&file))
    {
        file.close();
        return FILE_NOT_FOUND;
    }
    file.close();

    QDomElement level = doc.firstChildElement(QString("level"));
    if (level.isNull()) return NOT_WELL_FORMED;

    if(level.attributes().namedItem("levelLength").nodeValue().toInt() <= BASE_X_RESOLUTION) return NOT_WELL_FORMED;

    // creating the collections of blocks
    QDomElement envElement = level.firstChildElement(QString("environment"));
    if(envElement.isNull()) return NOT_WELL_FORMED;

    QDomElement block = envElement.firstChildElement(QString("block"));

    std::string type;

    while (!block.isNull())
    {
        if (!block.attributes().namedItem("type").nodeValue().isEmpty())
            type = block.attributes().namedItem("type").nodeValue().toStdString();
        else
            return INCONSISTENT_VALUES +0;

        if (block.attributes().namedItem("x").nodeValue().isEmpty()) return INCONSISTENT_VALUES +1;
        if (block.attributes().namedItem("y").nodeValue().isEmpty()) return INCONSISTENT_VALUES +2;
        if (block.attributes().namedItem("w").nodeValue().isEmpty()) return INCONSISTENT_VALUES +3;
        if (block.attributes().namedItem("h").nodeValue().isEmpty()) return INCONSISTENT_VALUES +4;
        if (block.attributes().namedItem("h").nodeValue().isEmpty()) return INCONSISTENT_VALUES +5;

        if(type == "paintImage")
        {
            if (block.attributes().namedItem("image").nodeValue().isEmpty() ) return INCONSISTENT_VALUES;
        }
        else
        {
            if (block.attributes().namedItem("color").nodeValue().isEmpty()) return INCONSISTENT_VALUES;
        }

        block = block.nextSibling().toElement();
    }

    //Creating the collection of enemies

    QDomElement inhabitantElement = level.firstChildElement(QString("enemies"));
    if(inhabitantElement.isNull()) return NOT_WELL_FORMED;

    QDomElement enemy = inhabitantElement.firstChildElement(QString("enemy"));
    std::string start;

    while (!enemy.isNull())
    {
        if (!enemy.attributes().namedItem("type").nodeValue().isEmpty())
            type = enemy.attributes().namedItem("type").nodeValue().toStdString();
        else
            return INCONSISTENT_VALUES +6;

        if (enemy.attributes().namedItem("x").nodeValue().isEmpty()) return INCONSISTENT_VALUES +7;
        if (enemy.attributes().namedItem("y").nodeValue().isEmpty()) return INCONSISTENT_VALUES +8;
        if (enemy.attributes().namedItem("w").nodeValue().isEmpty()) return INCONSISTENT_VALUES +9;
        if (enemy.attributes().namedItem("h").nodeValue().isEmpty()) return INCONSISTENT_VALUES +10;
        if (!enemy.attributes().namedItem("start").nodeValue().isEmpty())
            start = enemy.attributes().namedItem("start").nodeValue().toStdString();
        else
            return INCONSISTENT_VALUES+11;

        if(type == "paintImage")
        {
            if (enemy.attributes().namedItem("image").nodeValue().isEmpty()) return INCONSISTENT_VALUES +12;
        }
        else
        {
            if (enemy.attributes().namedItem("color").nodeValue().isEmpty()) return INCONSISTENT_VALUES+13;
        }

        if( !(start == "left" || start == "right") ) return INCONSISTENT_VALUES +14;

        enemy = enemy.nextSibling().toElement();
    }

    //Creating the collection of collects

    QDomElement collectElement = level.firstChildElement(QString("collects"));
    if(collectElement.isNull()) return NOT_WELL_FORMED;

    QDomElement collect = collectElement.firstChildElement(QString("collect"));

    while (!collect.isNull())
    {
        if (!collect.attributes().namedItem("type").nodeValue().isEmpty())
            type = collect.attributes().namedItem("type").nodeValue().toStdString();
        else
            return INCONSISTENT_VALUES +15;

        if (collect.attributes().namedItem("x").nodeValue().isEmpty()) return INCONSISTENT_VALUES +16;
        if (collect.attributes().namedItem("y").nodeValue().isEmpty()) return INCONSISTENT_VALUES +17;
        if (collect.attributes().namedItem("w").nodeValue().isEmpty()) return INCONSISTENT_VALUES +18;
        if (collect.attributes().namedItem("h").nodeValue().isEmpty()) return INCONSISTENT_VALUES +19;
        if (collect.attributes().namedItem("value").nodeValue().isEmpty()) return INCONSISTENT_VALUES +20;

        if(type == "paintImage")
        {
            if (collect.attributes().namedItem("image").nodeValue().isEmpty()) return INCONSISTENT_VALUES +21;
        }
        else
        {
            if (collect.attributes().namedItem("color").nodeValue().isEmpty()) return INCONSISTENT_VALUES + 22;
        }
        collect = collect.nextSibling().toElement();
    }

    //Creating the collection of backgrounds

    QDomElement bgElement = level.firstChildElement(QString("backgrounds"));
    if(bgElement.isNull()) return NOT_WELL_FORMED;

    QDomElement bg = bgElement.firstChildElement(QString("background"));

    while (!bg.isNull())
    {

        if (!bg.attributes().namedItem("type").nodeValue().isEmpty())
            type = bg.attributes().namedItem("type").nodeValue().toStdString();
        else
            return INCONSISTENT_VALUES + 23;

        if (bg.attributes().namedItem("x").nodeValue().isEmpty()) return INCONSISTENT_VALUES +24;
        if (bg.attributes().namedItem("y").nodeValue().isEmpty()) return INCONSISTENT_VALUES +25;
        if (bg.attributes().namedItem("w").nodeValue().isEmpty()) return INCONSISTENT_VALUES +26;
        if (bg.attributes().namedItem("h").nodeValue().isEmpty()) return INCONSISTENT_VALUES +27;

        if(type == "paintImage")
        {
            if (bg.attributes().namedItem("image").nodeValue().isEmpty()) return INCONSISTENT_VALUES +28;
        }
        else
        {
            if (bg.attributes().namedItem("color").nodeValue().isEmpty()) return INCONSISTENT_VALUES +29;
        }

        bg = bg.nextSibling().toElement();
    }

    //Creating the final block (traguardo)

    QDomElement fBlocks = level.firstChildElement(QString("finalBlocks"));

    if(fBlocks.isNull()) return NOT_WELL_FORMED;

    QDomElement fb = fBlocks.firstChildElement(QString("finalBlock"));

    while (!fb.isNull())
    {
        if (!fb.attributes().namedItem("type").nodeValue().isEmpty())
            type = fb.attributes().namedItem("type").nodeValue().toStdString();
        else
            return INCONSISTENT_VALUES +30;

        if (fb.attributes().namedItem("x").nodeValue().isEmpty()) return INCONSISTENT_VALUES +31;
        if (fb.attributes().namedItem("y").nodeValue().isEmpty()) return INCONSISTENT_VALUES +32;
        if (fb.attributes().namedItem("w").nodeValue().isEmpty()) return INCONSISTENT_VALUES +33;
        if (fb.attributes().namedItem("h").nodeValue().isEmpty()) return INCONSISTENT_VALUES +34;

        if(type == "paintImage")
        {
            if (fb.attributes().namedItem("image").nodeValue().isEmpty()) return INCONSISTENT_VALUES +35;
        }
        else
        {
            if (fb.attributes().namedItem("color").nodeValue().isEmpty()) return INCONSISTENT_VALUES +36;
        }
        fb = fb.nextSibling().toElement();
    }
    return LEVEL_LOADED;
}


/*!
  Creates an empty level.
*/
Level::Level()
{
    environment = QList<Block*>();
    enemies = QList<Enemy*>();
    collects = QList<Collect*>();
    backgroundElements = QList<BackgroundElement*>();
    finalBlocks = QList<Block*>();
}

/*!
  Destroys itself and all the WorldElements contained into it.
*/
Level::~Level()
{
    for(int i = 0; i < environment.size(); i++)
    {
        delete environment.at(i);
        environment.clear();
    }

    for(int i = 0; i < enemies.size(); i++)
    {
        delete enemies.at(i);
    }

    for(int i = 0; i < collects.size(); i++)
    {
        delete collects.at(i);
    }

    for(int i = 0; i < backgroundElements.size(); i++)
    {
        delete backgroundElements.at(i);
    }

    for(int i = 0; i < finalBlocks.size(); i++)
    {
        delete finalBlocks.at(i);
    }

    environment.clear();
    enemies.clear();
    collects.clear();
    backgroundElements.clear();
    finalBlocks.clear();

}

//! Returns the list of blocks
QList<Block*>* Level::getEnvironment()
{
        return &(this->environment);
}

//! Returns the list of enemies
QList<Enemy*>* Level::getEnemies()
{
        return &(this->enemies);
}

//! Returns the list of collectable elements
QList<Collect*>* Level::getCollects()
{
        return &(this->collects);
}

//! Returns the list of background elements
QList<BackgroundElement*>* Level::getBackgroundElements()
{
        return &(this->backgroundElements);
}

//! Returns the lenght of the level
int Level::getLevelLength()
{
    return levelLength;
}

//! Returns the list of endpoints of the level.
QList<Block*>* Level::getFinalBlocks()
{
    return &(this->finalBlocks);
}

/*!
  Checks whether an element is colliding with an other one.
*/
int Level::isColliding( WorldElement& actor , int newX, int newY, int newW, int newH, int *index)
{

    int isColliding = NOT_COLLIDING;

    WorldElement* e;

    if(newY >= BASE_Y_RESOLUTION)
    {
    	return IMMEDIATE_DEATH;
    }

    //check the enemies
    if(!actor.getIsImmortal())
    {
        for(int i = 0; i < this->enemies.size(); i++)
        {
            e = enemies.at(i);
            isColliding = checkCollisionWith(e ,actor, newX, newY, newW, newH, DEATHLY_COLLIDING);

            if (isColliding == DEATHLY_COLLIDING)
            {
                *index = i;
                return isColliding;
            }
        }
    }

    //here the environment is checked
    for(int i = 0; i < this->environment.size(); i++)
    {
    	e = environment.at(i);
        isColliding = checkCollisionWith(e ,actor, newX, newY, newW, newH, ENVIRONMENT_COLLIDING);

        if (isColliding == ENVIRONMENT_COLLIDING)
        {
            //*index = i;
            return isColliding;
    	}
    }

    //check the collectables
    for(int i = 0; i < this->collects.size(); i++)
    {
        e = collects.at(i);
        isColliding = checkCollisionWith(e ,actor, newX, newY, newW, newH, COLLECTABLE_COLLIDING);

        if (isColliding == COLLECTABLE_COLLIDING)
        {
            *index = i;
            return isColliding;
        }
    }
    return isColliding;
}

/*!
 * checks whether the position of an element overlaps another one
 */
int Level::checkCollisionWith(WorldElement* e, WorldElement& actor, int &newX, int &newY, int &newW, int &newH, int kindOfCollision)
{
    if(!e->isVisible())
        return NOT_COLLIDING;
    if(e == &actor)
        return NOT_COLLIDING;

    int isColliding = NOT_COLLIDING;

    //if the player reaches the beginning or the end of the level
    if(newX < 0 || (newX + newW) > (this->levelLength))
    {
    	isColliding = ENVIRONMENT_COLLIDING;
    }

    //if the base of the actor is not over the base of the element return true
    if((newX + newW) < e->getX() || (e->getX()+e->getWidth())<newX)
    {
        //isColliding = NOT_COLLIDING;
    }
    else
    {
        //if the side of the actor is not at the same height of the element return true
        if((newY + newH) < e->getY() || (e->getY()+e->getHeight()) < newY)
        {
            //isColliding =  NOT_COLLIDING;
        }
        else
        {
            isColliding =  kindOfCollision;
            return isColliding;
        }
    }
    return isColliding;
}

/*!
 	the level checks whether the player has reached the end of the level
 */
bool Level::checkEnd(int playerX, int playerY)
{
    int flagX;
    int flagY;
    int flagH;
    int flagW;

    for(int i = 0; i < finalBlocks.size(); i++)
    {
        flagX = this->finalBlocks.at(i)->getX();
        flagY = this->finalBlocks.at(i)->getY();
        flagH = this->finalBlocks.at(i)->getHeight();
        flagW = this->finalBlocks.at(i)->getWidth();

        if( !(playerX>(flagX+flagW)||playerX<flagX||playerY>(flagY+flagH)||playerY<flagY) )
            return true;
    }

    return false;
}
