#include "MainWindow.h"
#include "Level.h"
#include "GraphicLevel.h"
#include <iostream>

MainWindow::MainWindow()
{
    // Set window proprieties
    setWindowTitle("Run Sepp Run");
    setWindowIcon(QIcon(":/Icon/ico.gif"));

    // Set window position and size
    setGeometry(200, 200, 0, 0);
    setMinimumSize(800, 600);
    setMaximumSize(1680, 1050);

    createActions(); // Create buttons inside menu
    createMenus();  // Put menu together

    GraphicsView *view = new GraphicsView();
    view->setFocus();   // Enable its keyboard listener

    setCentralWidget(view); // Add view to the window

    //TEMP FOR TESTING
    Level *l1 = new Level();
    GraphicLevel *gl1 = new GraphicLevel();
    std::cout << Level::parseXML("level1.xml", l1, gl1);
}

void MainWindow::about()
{
    QMessageBox::about(this, "About Run Sepp Run",
                       "<b>Run Sepp Run preAlpha 0.01</b>"
                       "<p>Developers:<ul>"
                       "<li>Corneliu Ilisescu</li>"
                       "<li>Manuel Piubelli</li>"
                       "<li>Marco Seravalli</li>"
                       "<li>Patrick Clara</li></ul>"
                       "</p>");
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::createActions()
{
    // About action
    aboutAct = new QAction("&About", this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    // AboutQt action
    aboutQtAct = new QAction("AboutQt", this);
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

    // Exit action
    exitAct = new QAction("E&xit", this);
    exitAct->setShortcuts(QKeySequence::Close /*Quit*/);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createMenus()
{
    // Game Menu
    gameMenu = new QMenu("&Game");
    gameMenu->addAction(aboutAct);
    gameMenu->addAction(aboutQtAct);
    gameMenu->addAction(exitAct);

    // Menu Bar
    menuBar = new QMenuBar();
    setMenuBar(menuBar);
    menuBar->addMenu(gameMenu);
}

// Calles whenever a QCloseEvent is catched
void MainWindow::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton choice = QMessageBox::question(this,
                                                               "Exit", "Do you really want to exit?",
                                                               QMessageBox::Ok | QMessageBox::Cancel,
                                                               QMessageBox::Cancel);

    if(choice == QMessageBox::Cancel)
        event->ignore();
}
