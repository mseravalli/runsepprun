#include "MainWindow.h"
#include <QtGui>

MainWindow::MainWindow()
{
    createActions();
    createMenus();

    //statusBar()->showMessage( QApplication::translate("general", "Msg:") );

    //setWindowTitle("Sample");

    //setMinimumSize(800, 600);
    //setMaximumSize(800, 600);

    //GraphicsView *view = new GraphicsView();

    //view->setFocus();

    //setCentralWidget(view);
}

void MainWindow::about()
{
    QMessageBox::about(this, "About Run Sepp Run", "<b>Run Sepp Run preAlpha 0.01</b><p>Developers:<br />\tCorneliu Ilisescu<br />\tManuel Piubelli<br />\tMarco Serravalli<br />\tPatrick Clara</p>");
}

void MainWindow::createActions()
{
    aboutAct = new QAction("&About", this);
    aboutAct->setStatusTip("Show the application's About box");
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    exitAct = new QAction("E&xit", this);
    exitAct->setShortcuts(QKeySequence::Close);
    exitAct->setStatusTip("Exit the application");
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = new QMenu("&File");
    fileMenu->addAction(exitAct);
    fileMenu->addSeparator()->setText("Separator");
    fileMenu->addAction(aboutAct);


    QMenuBar *menuBar = new QMenuBar();
    setMenuBar(menuBar);
    menuBar->addMenu(fileMenu);
}

