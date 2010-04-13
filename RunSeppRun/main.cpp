#include <QApplication>
#include "MainWindow.h"
//
int main(int argc, char **argv)
{
    int retV;

    QApplication app(argc, argv);

    // MainWindow
    MainWindow *window = new MainWindow();
    (*window).show();

    retV = app.exec();

    delete window;

    return retV;
}
