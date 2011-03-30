#ifndef LEVEL_H
#define	LEVEL_H

class Character;
#include "Character.h"
#include "WorldElement.h"
#include <QList>
#include <string>
#include "GraphicLevel.h"

class Level {
public:
    Level();
    ~Level();
    static bool isColliding(const Character&, int, int);
    static int parseXML(std::string, Level*, GraphicLevel*);

    QList<WorldElement*> environment;
};

#endif
