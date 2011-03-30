TEMPLATE = app
TARGET = RunServerRun
QT += core \
    xml \
    network \
    qt3support
HEADERS += Arch.h \
    BackgroundElement.h \
    Block.h \
    Character.h \
    Collect.h \
    ConnectionReceiver.h \
    ConnectionSender.h \
    Connectionthread.h \
    Egg.h \
    Enemy.h \
    Globals.h \
    IsImmortalThread.h \
    Level.h \
    LogicEngine.h \
    Player.h \
    Receiver.h \
    Server.h \
    WorldElement.h
SOURCES += BackgroundElement.cpp \
    Block.cpp \
    Character.cpp \
    Collect.cpp \
    ConnectionReceiver.cpp \
    ConnectionSender.cpp \
    Connectionthread.cpp \
    Egg.cpp \
    Enemy.cpp \
    IsImmortalThread.cpp \
    Level.cpp \
    LogicEngine.cpp \
    Player.cpp \
    Receiver.cpp \
    Server.cpp \
    WorldElement.cpp \
    main.cpp
FORMS += 
RESOURCES += 
