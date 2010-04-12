/* 
 * File:   WorldElement.h
 * Author: marco
 *
 * Created on April 12, 2010, 6:02 PM
 */

#ifndef _WORLDELEMENT_H
#define	_WORLDELEMENT_H

class WorldElement {
public:
    WorldElement();
    virtual int getX();
    virtual int getY();
    virtual int getWidth();
    virtual int getHeight();

protected:
    int posX;
    int posY;
    int width;
    int height;

private:

};

#endif	/* _WORLDELEMENT_H */

