#ifndef MAINMENU_H
#define MAINMENU_H

#include <QtGui>
class MainWindow;
class Client;

class MainMenu : public QWidget {

    Q_OBJECT

public:
    MainMenu(MainWindow *window);
    ~MainMenu();
    void openPauseMenu();
    void openMainMenu();

private slots:
    void exit();
    void connectToServer();
    void resumeCurrentGame();
    void backToMenu();

private:

    MainWindow *window;
    QVBoxLayout *layout;
    QHBoxLayout *hLayout;

    QPushButton *exitButton;
    QPushButton *connectButton;
    QLineEdit *serverAddressLine;
    QLineEdit *serverPortLine;

    QPushButton *resumeGame;
    QPushButton *backToMainMenu;

    void hideAll();

    void paintEvent(QPaintEvent*);

};


#endif // MAINMENU_H
