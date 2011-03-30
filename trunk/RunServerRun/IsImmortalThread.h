#ifndef ISIMMORTALTHREAD_H
#define ISIMMORTALTHREAD_H

#include <QThread>
class Player;

//! Makes the player immortal when needed.
/*!
        The thread sets a passed variable as true after a selectable amount of time
 */
class IsImmortalThread : public QThread
{
public:
    IsImmortalThread(bool* isImm);
    void setTime(int);
    void run();

private:
    int time;
    bool* isImmortal;
};

#endif
