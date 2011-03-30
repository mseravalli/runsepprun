#ifndef PAUSEMENU_H
#define PAUSEMENU_H

class MainWindow;
#include <QtGui>

//!  Pause menu.
/*!
  This class creates and handles the actions available in the pause menu.
*/
class PauseMenu : public QWidget
{

    Q_OBJECT

public:
    PauseMenu(MainWindow *window);
    ~PauseMenu();

private slots:
    void resume();
    void mainMenu();

private:
    QLabel *label;
    QPushButton *resumeButton;
    QPushButton *mainMenuButton;
    QVBoxLayout *layout;
    QHBoxLayout *hLayout;
    MainWindow *window;
};

#endif
