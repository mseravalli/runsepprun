TEMPLATE = app
TARGET = TestRunSeppRun
QT += core \
    gui \
    xml \
    network \
    svg \
    qt3support \
    phonon \
    testlib
HEADERS += TestClient.h \
    ../RunSeppRun/Client.h \
    ../RunSeppRun/ConnectionSender.h \
    ../RunSeppRun/ConnectionReceiver.h \
    ../RunSeppRun/GraphicsView.h \
    ../RunSeppRun/GraphicLevel.h \
    ../RunSeppRun/GraphicItem.h \
    ../RunSeppRun/GraphicsScene.h \
    ../RunSeppRun/MainWindow.h \
    ../RunSeppRun/MainMenu.h \
    ../RunSeppRun/AudioEffects.h \
    ../RunSeppRun/PauseMenu.h \
    ../RunSeppRun/UserProfile.h \
    ../RunSeppRun/StoryLevelButton.h
SOURCES += TestClient.cpp \
    main.cpp \
    ../RunSeppRun/Client.cpp \
    ../RunSeppRun/ConnectionSender.cpp \
    ../RunSeppRun/ConnectionReceiver.cpp \
    ../RunSeppRun/GraphicsView.cpp \
    ../RunSeppRun/GraphicLevel.cpp \
    ../RunSeppRun/GraphicItem.cpp \
    ../RunSeppRun/GraphicsScene.cpp \
    ../RunSeppRun/MainWindow.cpp \
    ../RunSeppRun/MainMenu.cpp \
    ../RunSeppRun/AudioEffects.cpp \
    ../RunSeppRun/PauseMenu.cpp \
    ../RunSeppRun/UserProfile.cpp \
    ../RunSeppRun/StoryLevelButton.cpp
FORMS += 
RESOURCES += 
QMAKE_CXXFLAGS += -fprofile-arcs \
    -ftest-coverage
QMAKE_LFLAGS += -fprofile-arcs
