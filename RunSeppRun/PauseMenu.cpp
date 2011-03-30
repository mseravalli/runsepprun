#include "PauseMenu.h"
#include "Globals.h"
#include "MainWindow.h"
#include "MainMenu.h"
#include "Client.h"

/*!
  It creates the PauseMenu.
*/
PauseMenu::PauseMenu(MainWindow *window)
{
    // init
    this->window = window;

    // Gereral window
    setWindowOpacity(0.9);

    // Buttons
    layout = new QVBoxLayout();
    hLayout = new QHBoxLayout();

    label = new QLabel("<h2 align=\"center\">Pause menu</h2>");
    resumeButton = new QPushButton("&Resume");
    resumeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(resumeButton, SIGNAL(clicked()), this, SLOT(resume()));
    mainMenuButton = new QPushButton("&Main Menu");
    mainMenuButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(mainMenuButton, SIGNAL(clicked()), this, SLOT(mainMenu()));

    layout->insertSpacing(0, 100);
    layout->addWidget(label);
    layout->insertSpacing(1, 100);
    layout->addWidget(resumeButton);
    layout->addWidget(mainMenuButton);
    layout->insertSpacing(5, 250);

    hLayout->insertSpacing(0, 300);
    hLayout->addLayout(layout);
    hLayout->insertSpacing(2, 300);

    setLayout(hLayout);
}

void PauseMenu::resume()
{
    window->pauseMenu->hide();
    window->view->show();
    window->setFocus();
    window->view->setFocus();
    window->view->timer->start(TIMER_X_MSEC);
}

void PauseMenu::mainMenu()
{

    window->getClient()->diconnectFromServer();

    window->pauseMenu->hide();
    window->menu->show();
    window->setFocus();
    window->menu->setFocus();    
    window->view->unloadLevel();


}

/*!
  It destroys the PauseMenu.
*/
PauseMenu::~PauseMenu()
{
    delete label;
    delete resumeButton;
    delete mainMenuButton;
    delete layout;
    delete hLayout;
    label = NULL;
    resumeButton = NULL;
    mainMenuButton = NULL;
    layout = NULL;
    hLayout = NULL;
}
