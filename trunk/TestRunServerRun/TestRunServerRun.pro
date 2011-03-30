TEMPLATE = app
TARGET = TestRunServerRun
QT += core \
    gui \
    sql \
    xml \
    network \
    svg \
    qt3support \
    testlib
HEADERS += TestEgg.h \
    TestEnemy.h \
    TestPlayer.h \
    TestServer.h \
    TestLevel.h \
    ../RunServerRun/Receiver.h \
    ../RunServerRun/Connectionthread.h \
    ../RunServerRun/ConnectionReceiver.h \
    ../RunServerRun/ConnectionSender.h \
    ../RunServerRun/Arch.h \
    ../RunServerRun/BackgroundElement.h \
    ../RunServerRun/Block.h \
    ../RunServerRun/Character.h \
    ../RunServerRun/Collect.h \
    ../RunServerRun/Egg.h \
    ../RunServerRun/Enemy.h \
    ../RunServerRun/Globals.h \
    ../RunServerRun/IsImmortalThread.h \
    ../RunServerRun/Level.h \
    ../RunServerRun/LogicEngine.h \
    ../RunServerRun/Player.h \
    ../RunServerRun/Server.h \
    ../RunServerRun/WorldElement.h
SOURCES += TestEgg.cpp \
    TestEnemy.cpp \
    TestPlayer.cpp \
    TestServer.cpp \
    TestLevel.cpp \
    ../RunServerRun/Receiver.cpp \
    ../RunServerRun/Connectionthread.cpp \
    ../RunServerRun/ConnectionReceiver.cpp \
    ../RunServerRun/ConnectionSender.cpp \
    ../RunServerRun/BackgroundElement.cpp \
    ../RunServerRun/Block.cpp \
    ../RunServerRun/Character.cpp \
    ../RunServerRun/Collect.cpp \
    ../RunServerRun/Egg.cpp \
    ../RunServerRun/Enemy.cpp \
    ../RunServerRun/IsImmortalThread.cpp \
    ../RunServerRun/Level.cpp \
    ../RunServerRun/LogicEngine.cpp \
    ../RunServerRun/Player.cpp \
    ../RunServerRun/Server.cpp \
    ../RunServerRun/WorldElement.cpp \
    main.cpp
FORMS += 
RESOURCES += 
QMAKE_CXXFLAGS += -fprofile-arcs \
    -ftest-coverage
QMAKE_LFLAGS += -fprofile-arcs
