#include "Level.h"
#include <QDomDocument>
#include <QFile>

void Level::parseXML(std::string path){

	 QDomDocument doc("mydocument");
	 QFile file("mydocument.xml");
	 if (!file.open(QIODevice::ReadOnly))
	     return;
	 if (!doc.setContent(&file)) {
	     file.close();
	     return;
	 }
	 file.close();


}

Level::Level(std::string path) {

	environment = QList<Block>();

	parseXML(path);
}





bool Level::isColliding(const Character& actor , int newX, int newY){

    WorldElement e = WorldElement(50,50,50,50);

    int cornerX;
    int cornerY;

    //0 = TOP
    //1 = RIGHT
    //2 = BOTTOM
    //3 = LEFT

    //to apply to every object in the collections


    //if one of the corners is is colliding with another block

    

    //top left corner
    cornerX = newX;
    cornerY = newY;
    if (cornerX > e.getX() && cornerX < (e.getX() + e.getWidth())){
        if(cornerY > e.getY() && cornerY < (e.getY() + e.getHeight())){
            return true;
        }
    }
    
    //top right corner
    cornerX = newX + actor.getWidth();
    cornerY = newY;
    if (cornerX > e.getX() && cornerX < (e.getX() + e.getWidth())){
        if(cornerY > e.getY() && cornerY < (e.getY() + e.getHeight())){
            return true;
        }
    }


    //bottom left corner
    cornerX = newX;
    cornerY = newY + actor.getHeight();
    if (cornerX > e.getX() && cornerX < (e.getX() + e.getWidth())){
        if(cornerY > e.getY() && cornerY < (e.getY() + e.getHeight())){
            return true;
        }
    }


    //bottom right corner
    cornerX = newX + actor.getWidth();
    cornerY = newY + actor.getHeight();
    if (cornerX > e.getX() && cornerX < (e.getX() + e.getWidth())){
        if(cornerY > e.getY() && cornerY < (e.getY() + e.getHeight())){
            return true;
        }
    }

    return false;
}
