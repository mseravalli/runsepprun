#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtGui>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void about();

private:
    void createActions();
    void createMenus();

    QMenu *gameMenu;
    QMenuBar *menuBar;

    QAction *exitAct;
    QAction *aboutAct;
};

#endif
