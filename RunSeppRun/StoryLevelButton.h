#ifndef STORYLEVELBUTTON_H
#define STORYLEVELBUTTON_H

#include <QPushButton>

class StoryLevelButton : public QPushButton
{

    Q_OBJECT

public:
    StoryLevelButton(QString);
signals:
    void loadLevel(QString);
private slots:
    void goToLevel();
private:
    QString name;
};

#endif // STORYLEVELBUTTON_H
