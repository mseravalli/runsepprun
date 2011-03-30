#include <QApplication>
#include "MainWindow.h"

int main(int argc, char **argv)
{
    int retV;

    QApplication app(argc, argv);
    app.setApplicationName("RunSeppRun");

    // MainWindow
    MainWindow *window = new MainWindow();
    (*window).show();

    // Exec main loop
    retV = app.exec();

    delete window;

    return retV;
}

