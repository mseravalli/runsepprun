#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
class MainMenu;
class Client;
class GraphicsView;

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    MainMenu* menu;
    GraphicsView* view;

    Client* getClient();

private:
    QHBoxLayout *centralLayout;
    QWidget *centralWid;

    Client* client;

};


#endif // MAINWINDOW_H
