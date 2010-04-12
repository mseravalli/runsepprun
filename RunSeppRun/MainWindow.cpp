#include "MainWindow.h"

MainWindow::MainWindow()
{
    createActions();
    createMenus();

    setWindowTitle("Run Sepp Run");

    setMinimumSize(800, 600);
    setMaximumSize(1680, 1050);

    //GraphicsView *view = new GraphicsView();

    //view->setFocus();

    //setCentralWidget(view);
}

void MainWindow::about()
{
    QMessageBox::about(this, "About Run Sepp Run",
                       "<b>Run Sepp Run preAlpha 0.01</b>"
                       "<p>Developers:<ul>"
                       "<li>Corneliu Ilisescu</li>"
                       "<li>Manuel Piubelli</li>"
                       "<li>Marco Serravalli</li>"
                       "<li>Patrick Clara</li></ul>"
                       "</p>");
}

void MainWindow::createActions()
{
    aboutAct = new QAction("&About", this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    exitAct = new QAction("E&xit", this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createMenus()
{
    // Game Menu
    gameMenu = new QMenu("&Game");
    gameMenu->addAction(aboutAct);
    gameMenu->addAction(exitAct);

    // Menu Bar
    menuBar = new QMenuBar();
    setMenuBar(menuBar);
    menuBar->addMenu(gameMenu);
}
