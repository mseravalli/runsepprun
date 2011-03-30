#include "TestEgg.h"

#include "qdebug.h"
#include <QtGui>
#include <string>
#include "../RunServerRun/Level.h"
#include "../RunServerRun/WorldElement.h"
#include "../RunServerRun/Collect.h"
#include "../RunServerRun/Block.h"
#include "../RunServerRun/Character.h"
#include "../RunServerRun/Player.h"
#include "../RunServerRun/Enemy.h"
#include "../RunServerRun/Globals.h"
#include "../RunServerRun/Egg.h"
#include "../RunServerRun/BackgroundElement.h"


//Tests Egg::Launch and Egg:move
void TestEgg::testAdvance(){
        Level level;
        level.parseXML("test.xml");
        Player *player = new Player(0, 0, 10, 10, level, NULL);
        Egg *egg = new Egg(10,10,5,5,*player,level);
        egg->launch(player->getDirectionX());
        egg->move();
        QCOMPARE(egg->getX() , (6+ player->getWidth()/2)*player->getDirectionX());

        delete egg;
        delete player;

}

//Tests If an Egg hits and kills an enemy
void TestEgg::testKill(){

        Level level;
        level.parseXML("test.xml");
        Player *player = new Player(60, 12, 10, 10, level, NULL);

        //test that 1 life is taken from enemy
        Egg *egg = new Egg(10,10,5,5,*player,level);
        Enemy * enemy = level.getEnemies()->at(0);
        enemy->setVisible(true);
        egg->launch(RIGHT_DIRECTION);
        egg->move();
        if(egg->isVisible())
            egg->move();

        if(egg->isVisible())
            egg->move();

        QCOMPARE(enemy->getLife(),1);
        QCOMPARE(egg->isVisible(),false);

        //test that enemy dies
        egg = new Egg(10,10,5,5,*player,level);
        egg->launch(RIGHT_DIRECTION);
        egg->move();
        if(egg->isVisible())
            egg->move();

        if(egg->isVisible())
            egg->move();

        QCOMPARE(enemy->getLife(),0);
        QCOMPARE(egg->isVisible(),false);

}

  //Tests if the egg is broken when hitting a block
void TestEgg::testSmash(){
    Level level;
    level.parseXML("test.xml");
    Player *player = new Player(480, 520, 10, 10, level, NULL);
    Egg *egg = new Egg(10,10,5,5,*player,level);
    egg->launch(1);
    egg->move();
    egg->move();
    egg->move();
    QCOMPARE(egg->isVisible(),false);
}


