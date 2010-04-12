/* 
 * File:   Level.h
 * Author: marco
 *
 * Created on April 12, 2010, 3:34 PM
 */

#ifndef _LEVEL_H
#define	_LEVEL_H

class Level {
public:
    Level();
    Level(const Level& orig);
    virtual ~Level();

    static bool isColliding();

private:



};

#endif	/* _LEVEL_H */

