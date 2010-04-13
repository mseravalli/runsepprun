#ifndef LEVEL_H
#define	LEVEL_H

class Character;
#include "Character.h"
#include "Block.h"
#include <QList>
#include <string>

class Level {
public:
    Level(std::string);
    static bool isColliding(const Character&, int, int);

private:

    QList<Block> environment;


    int parseXML(std::string);

};

#endif
