#ifndef LEVEL_H
#define	LEVEL_H

class Character;
#include "Character.h"
#include "Block.h"
#include <QList>
#include <iostream>
#include <string>

class Level {
public:
    Level(std::string);
    static bool isColliding(const Character&, int, int);

private:

    QList<Block> environment;


    bool parseXML(std::string);

};

#endif
