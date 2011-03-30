#include "UserProfile.h"

/*!
 * a new User profile is initialized
 */
UserProfile::UserProfile(QString name, int uLvls, QList<QString> cLvls){
    this->name = name;
    this->unlockedLvls = uLvls;
    this->customLvls = cLvls;
}

QList<QString> UserProfile::getCustomLvls(){
    return customLvls;
}

QString UserProfile::getName(){
    return name;
}

int UserProfile::getUnlockedLvls(){
    return unlockedLvls;
}
