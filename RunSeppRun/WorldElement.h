#ifndef WORLDELEMENT_H
#define	WORLDELEMENT_H

class WorldElement {
public:
    WorldElement();
    WorldElement(int x, int y, int w, int h);
    virtual int getX() const;
    virtual int getY() const;
    virtual int getWidth() const;
    virtual int getHeight() const;

protected:
    int posX;
    int posY;
    int width;
    int height;

private:

};

#endif

