TEMPLATE = app
TARGET = RunSeppRun
QT += core \
    gui \
    xml \
    network \
    svg \
    qt3support
HEADERS += UDPSender.h \
    images.h \
    UDPReceiver.h \
    Client.h \
    GraphicItem.h \
    GraphicLevel.h \
    GraphicsScene.h \
    GraphicsView.h \
    MainMenu.h \
    MainWindow.h
SOURCES += UDPSender.cpp \
    UDPReceiver.cpp \
    Client.cpp \
    GraphicItem.cpp \
    GraphicLevel.cpp \
    GraphicsScene.cpp \
    GraphicsView.cpp \
    MainMenu.cpp \
    MainWindow.cpp \
    main.cpp
FORMS += 
RESOURCES += main.qrc
