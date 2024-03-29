#include "Level.h"
#include <QtXml>
#include <QtGui>
#include <iostream>
#include <fstream>
#include <QtDebug>
#include <cstdlib>
#include "Block.h"

int Level::parseXML(std::string path, Level* levelRet, GraphicLevel* graphicLevelRet)
{
    /*
      POSSIBLE ERRORS:
      1-Can not read file
      2-No level
      3-No environment or enemies
      4-Inconsistent entries
    */

    // Read file
    int fileSize;
    char* buf;

    std::ifstream inFile;
    inFile.open(path.c_str(), std::ios::in | std::ios::binary);

    if(!inFile.is_open())
        return 1;

    inFile.seekg(0, std::ios::end);
    fileSize = inFile.tellg();
    buf = new char[ fileSize ];

    inFile.seekg(0, std::ios::beg);
    inFile.read(buf,fileSize);
    inFile.close();

    // Parse file
    QDomDocument levelDom;
    levelDom.setContent(QString(buf));

    QDomNode level;
    QDomNode environment;
    QDomNode enemies;
    QDomNode tmp;

    // Get level
    tmp = levelDom.firstChild();
    while(!tmp.isNull())
    {
        if(!tmp.isNull() && tmp.nodeName() == QString("level"))
            level = tmp;
        else if(!tmp.isNull())
        {
            tmp = tmp.nextSibling();
            continue;
        }
        else if(tmp.isNull() && !level.isNull())
        {
            tmp = tmp.nextSibling();
            break;
        }
        else if(tmp.isNull() && level.isNull())
            return 2;

        tmp = tmp.nextSibling();
    }

    // Get environment and enemies
    tmp = level.firstChild();
    while(1)
    {
        if(!tmp.isNull() && tmp.nodeName() == QString("environment"))
            environment = tmp;
        else if(!tmp.isNull() && tmp.nodeName() == QString("enemies"))
            enemies = tmp;
        else if(!tmp.isNull())
        {
            tmp = tmp.nextSibling();
            continue;
        }
        else if(tmp.isNull() && !enemies.isNull() && !environment.isNull())
        {
            tmp = tmp.nextSibling();
            break;
        }
        else if(tmp.isNull() && (enemies.isNull() || environment.isNull()))
            return 3;

        tmp = tmp.nextSibling();
    }

    // Parse environment subtree
    tmp = environment.firstChild();
    while(!tmp.isNull())
    {
        if(tmp.nodeName() != QString("block"))
            continue;

        // Do something
        int x, y, w, h;
        
        if(!tmp.attributes().namedItem("x").nodeValue().isEmpty())
            x = tmp.attributes().namedItem("x").nodeValue().toInt();
        else
            return 4;

        if(!tmp.attributes().namedItem("y").nodeValue().isEmpty())
            y = tmp.attributes().namedItem("y").nodeValue().toInt();
        else
            return 4;

        if(!tmp.attributes().namedItem("w").nodeValue().isEmpty())
            w = tmp.attributes().namedItem("w").nodeValue().toInt();
        else
            return 4;

        if(!tmp.attributes().namedItem("h").nodeValue().isEmpty())
            h = tmp.attributes().namedItem("h").nodeValue().toInt();
        else
            return 4;

        WorldElement *tmpBlock = new Block(x,y,w,h);
        GraphicItem *tmpItem = new GraphicItem(tmpBlock,w,h);

        levelRet->environment.append(tmpBlock);
        graphicLevelRet->graphicWorld.append(tmpItem);


        // TEMP FOR TESTING
        qDebug() << tmp.nodeName() << tmp.attributes().namedItem("type").nodeValue();

        tmp = tmp.nextSibling();
    }

    // Parse enemies subtree
    tmp = enemies.firstChild();
    while(!tmp.isNull())
    {
        if(tmp.nodeName() != QString("enemy"))
            continue;

        // Do something
        qDebug() << tmp.nodeName() << tmp.attributes().namedItem("type").nodeValue();

        tmp = tmp.nextSibling();
    }

    return 0;
}

Level::Level()
{
    environment = QList<WorldElement*>();
}

Level::~Level()
{
    // distruggere tutti gli elementi nella lista
}

bool Level::isColliding(const Character& actor , int newX, int newY){

    int actorWidth = actor.getWidth();
    int actorHeigth = actor.getHeight();

    //to apply to every object in the collections
    WorldElement e = WorldElement(50,50,50,50);

    //if the base of the actor is not over the base of the element return true
    if((newX + actorWidth)< e.getX() || (e.getX()+e.getWidth())<newX){
        return false;
    } else {

        //if the side of the actor is not at the same height of the element return true
        if((newY + actorHeigth)<e.getY() || (e.getY()+e.getHeight()) < newY){
            return false;
        } else {
            return true;
        }
    }


}
