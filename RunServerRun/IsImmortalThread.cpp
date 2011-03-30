#include "IsImmortalThread.h"
#include "Player.h"

/*!
 * the thread is contructed
 */
IsImmortalThread::IsImmortalThread(bool* isImm){
//    this->player = player;
    this->time = 0;
    isImmortal = isImm;
}

/*!
 * the thread starts, the threads sleeps for a time seconds
 */
void IsImmortalThread::run(){
    sleep(time);
    *isImmortal = false;
//    player->setIsImmortal(false);
    time = 0;
}

//! Sets the time to sleep
void IsImmortalThread::setTime(int time){
    this->time = time;
}
