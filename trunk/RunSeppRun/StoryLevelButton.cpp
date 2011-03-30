#include "StoryLevelButton.h"

StoryLevelButton::StoryLevelButton(QString name){
    this->name = name;
    connect(this, SIGNAL(clicked()), this, SLOT(goToLevel()));
}

void StoryLevelButton::goToLevel(){
    emit loadLevel(name);
}
