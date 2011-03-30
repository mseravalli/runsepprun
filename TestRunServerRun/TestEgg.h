#ifndef TESTEGG_H_
#define TESTEGG_H_

#include <QtTest/QtTest>
#include <QObject>

class TestEgg: public QObject{

        Q_OBJECT

private slots:

        void testAdvance();
        void testKill();
        void testSmash();

};

#endif /* TESTEGG_H_ */
