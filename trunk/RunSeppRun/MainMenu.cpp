#include "MainMenu.h"
#include "MainWindow.h"
#include "Client.h"
#include "GraphicsView.h"


MainMenu::MainMenu(MainWindow *window){
    this->window = window;

    layout = new QVBoxLayout();
    hLayout = new QHBoxLayout();

    exitButton = new QPushButton("&Quit Game");
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exit()));
    serverAddressLine = new QLineEdit("127.0.0.1", this);
    serverPortLine = new QLineEdit("45453");
    connectButton = new QPushButton("Connect to sever");
    connect(connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
    resumeGame = new QPushButton("Resume game");
    connect(resumeGame, SIGNAL(clicked()), this, SLOT(resumeCurrentGame()));
    backToMainMenu = new QPushButton("Back to main menu");
    connect(backToMainMenu, SIGNAL(clicked()), this, SLOT(backToMenu()));


    layout->insertSpacing(0, 500);
    layout->addWidget(exitButton);
    layout->addWidget(serverAddressLine);
    layout->addWidget(serverPortLine);
    layout->addWidget(connectButton);
    layout->addWidget(resumeGame);
    layout->addWidget(backToMainMenu);
    layout->insertSpacing(8,110);
    layout->setSpacing(0);

    hLayout->insertSpacing(0,250);
    hLayout->addLayout(layout);
    hLayout->insertSpacing(2,250);

    setLayout(hLayout);

    hideAll();

    openMainMenu();
}

MainMenu::~MainMenu(){    
    window = NULL;    
    delete exitButton;
    exitButton = NULL;
    delete serverAddressLine;
    serverAddressLine = NULL;
    delete serverPortLine;
    serverPortLine = NULL;
    delete connectButton;
    connectButton = NULL;

    delete resumeGame;
    resumeGame = NULL;
    delete backToMainMenu;
    backToMainMenu = NULL;


    delete layout;
    layout = NULL;
    delete hLayout;
    hLayout = NULL;

}

void MainMenu::exit(){
    window->close();
}

void MainMenu::connectToServer(){
    QString address = serverAddressLine->text();

    bool ok;
    quint16 port = (quint16) serverPortLine->text().toUInt(&ok, 10);
    if(!ok){
        QMessageBox::about(window, "Invalid port",
                        "Insert a valid port.");
            return;
    }
    window->getClient()->setServerAddress(address, port);

    window->getClient()->connectToServer();
}

void MainMenu::hideAll(){
	exitButton->hide();
	connectButton->hide();
	serverAddressLine->hide();
	serverPortLine->hide();
	resumeGame->hide();
	backToMainMenu->hide();
}

void MainMenu::openPauseMenu(){
        hideAll();
	this->show();
	resumeGame->show();
	backToMainMenu->show();

}


void MainMenu::resumeCurrentGame(){
	hideAll();
	this->hide();
	window->view->resumeGame();
}


void MainMenu::backToMenu(){

	window->getClient()->disconnectFromServer();

	hideAll();
	exitButton->show();
	connectButton->show();
	serverAddressLine->show();
	serverPortLine->show();
}

void MainMenu::openMainMenu(){

	this->show();

	hideAll();
	exitButton->show();
	connectButton->show();
	serverAddressLine->show();
	serverPortLine->show();
}

void MainMenu::paintEvent(QPaintEvent* pe){
    QPainter* pPainter = new QPainter(this);
    pPainter->drawPixmap(rect(), QPixmap(":/images/menu.png"));
    delete pPainter;
    QWidget::paintEvent(pe);
}
