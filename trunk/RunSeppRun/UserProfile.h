#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QtGui>

/*!
	this class contains some information about the user, like the name, it's
	custom levels and how many level s/he has passed in the story mode
 */
class UserProfile
{
public:
    UserProfile(QString, int, QList<QString>);
    QString getName();
    int getUnlockedLvls();
    QList<QString> getCustomLvls();

private:
    QString name;
    int unlockedLvls;
    QList<QString> customLvls;

};

#endif // USERPROFILE_H
