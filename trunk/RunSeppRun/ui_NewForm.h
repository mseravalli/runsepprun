/********************************************************************************
** Form generated from reading ui file 'NewForm.ui'
**
** Created: Wed Apr 7 16:49:01 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_NEWFORM_H
#define UI_NEWFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewForm
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NewForm)
    {
        if (NewForm->objectName().isEmpty())
            NewForm->setObjectName(QString::fromUtf8("NewForm"));
        NewForm->resize(445, 307);
        centralwidget = new QWidget(NewForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(190, 150, 131, 27));
        NewForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(NewForm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 445, 22));
        NewForm->setMenuBar(menubar);
        statusbar = new QStatusBar(NewForm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        NewForm->setStatusBar(statusbar);

        retranslateUi(NewForm);

        QMetaObject::connectSlotsByName(NewForm);
    } // setupUi

    void retranslateUi(QMainWindow *NewForm)
    {
        NewForm->setWindowTitle(QApplication::translate("NewForm", "NewForm", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("NewForm", "push me bastard!!", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(NewForm);
    } // retranslateUi

};

namespace Ui {
    class NewForm: public Ui_NewForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWFORM_H
