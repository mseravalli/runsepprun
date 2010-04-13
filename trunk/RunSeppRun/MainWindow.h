#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtGui>
#include "GraphicsView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent*);

private slots:
    void about();
    void aboutQt();

private:
    void createActions();
    void createMenus();

    QMenu *gameMenu;
    QMenuBar *menuBar;

    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};

#endif
