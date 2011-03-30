#include "MainWindow.h"
#include "../RunServerRun/Globals.h"
#include "MainMenu.h"
#include "Client.h"
#include "GraphicsView.h"

MainWindow::MainWindow(){
    // Set window proprieties
    setWindowTitle("Run Sepp Run");
    setWindowIcon(QIcon(":/images/ico.gif"));

    // Set window position and size
    setGeometry(200, 200, 0, 0);
    setMinimumSize(BASE_X_RESOLUTION, BASE_Y_RESOLUTION);
    setMaximumSize(BASE_X_RESOLUTION, BASE_Y_RESOLUTION);

    centralLayout = new QHBoxLayout();

    menu = new MainMenu(this);
    view = new GraphicsView(this);

    centralLayout->addWidget(menu);
    centralLayout->addWidget(view);
    view->hide();

    centralWid = new QWidget();
    centralWid->setLayout(centralLayout);

    setCentralWidget(centralWid);

    client = new Client(this);
}

MainWindow::~MainWindow(){
    delete menu;
    menu = NULL;
    delete view;
    view = NULL;
    delete centralLayout;
    centralLayout = NULL;
    delete centralWid;
    centralWid = NULL;
    delete client;
    client = NULL;
}

Client* MainWindow::getClient(){
    return client;
}
