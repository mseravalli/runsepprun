#include <QtCore>
#include <QCoreApplication>

#include "TestLevel.h"
#include "TestPlayer.h"
#include "TestEnemy.h"
#include "TestEgg.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestLevel *testLevel = new TestLevel();
    TestPlayer *testPlayer = new TestPlayer();
    TestEnemy  *testEnemy = new TestEnemy();
    TestEgg *testEgg = new TestEgg();

    QTest::qExec(testLevel, argc, argv);
    QTest::qExec(testPlayer, argc, argv);
    QTest::qExec(testEnemy, argc, argv);
    QTest::qExec(testEgg, argc, argv);
	
    return a.exec();
}
