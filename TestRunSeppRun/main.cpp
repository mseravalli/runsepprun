#include <QtCore>
#include <QCoreApplication>
#include <QtTest/QtTest>

#include "TestClient.h"

int main(int argc, char *argv[])
{

	QCoreApplication a(argc, argv);

	TestClient* testClient = new TestClient();

	QTest::qExec(testClient, argc, argv);
    return 0;
}
