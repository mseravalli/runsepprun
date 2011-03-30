#ifndef WORLDELEMENT_H
#define	WORLDELEMENT_H

class Level;
#include <string>
#include <QObject>

//!  Level elements.
/*!
  This class is a very general representation of all the possible elements inside a level.
*/
class WorldElement : public QObject
{
public:

    WorldElement(int x, int y, int w, int h, Level*);

    int getX();
    int getY();
    int getWidth();
    int getHeight();
    virtual void move();
    void setVelocityX(double);
    double getVelocityX();

    void setVisible(bool);
    bool isVisible();
    double round(double);
    virtual int getDirectionX();
    virtual int getDirectionY();
    bool getIsAbleToJump();
    virtual double getJumpingForce();
    bool getIsImmortal();
    void setIsImmortal(bool);

protected:
    int posX;
    int posY;
    int width;
    int height;

    double velocityX;
    double velocityY;

    Level* level;

    int directionX;
    int directionY;
    bool isImmortal;

    double jumping_force;
    bool isAbleToJump;

private:
    bool visible;

};

#endif

