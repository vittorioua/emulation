/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include <console.h>

QT_BEGIN_NAMESPACE

class Ui_Server
{
public:
    QAction *actionAbout_the_program;
    QAction *actionHelp;
    QWidget *centralWidget;
    Console *console;
    QMenuBar *menuBar;
    QMenu *menuInfo;

    void setupUi(QMainWindow *Server)
    {
        if (Server->objectName().isEmpty())
            Server->setObjectName(QStringLiteral("Server"));
        Server->resize(510, 120);
        Server->setMinimumSize(QSize(510, 120));
        Server->setMaximumSize(QSize(510, 120));
        Server->setStyleSheet(QStringLiteral(""));
        actionAbout_the_program = new QAction(Server);
        actionAbout_the_program->setObjectName(QStringLiteral("actionAbout_the_program"));
        actionHelp = new QAction(Server);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        centralWidget = new QWidget(Server);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        console = new Console(centralWidget);
        console->setObjectName(QStringLiteral("console"));
        console->setGeometry(QRect(0, 0, 511, 99));
        console->setStyleSheet(QStringLiteral("border: 0px;"));
        Server->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Server);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 510, 20));
        menuInfo = new QMenu(menuBar);
        menuInfo->setObjectName(QStringLiteral("menuInfo"));
        Server->setMenuBar(menuBar);

        menuBar->addAction(menuInfo->menuAction());
        menuInfo->addAction(actionAbout_the_program);
        menuInfo->addAction(actionHelp);

        retranslateUi(Server);

        QMetaObject::connectSlotsByName(Server);
    } // setupUi

    void retranslateUi(QMainWindow *Server)
    {
        Server->setWindowTitle(QApplication::translate("Server", "Server", 0));
        actionAbout_the_program->setText(QApplication::translate("Server", "About the program", 0));
        actionHelp->setText(QApplication::translate("Server", "Help", 0));
        actionHelp->setShortcut(QApplication::translate("Server", "F1", 0));
        menuInfo->setTitle(QApplication::translate("Server", "Info", 0));
    } // retranslateUi

};

namespace Ui {
    class Server: public Ui_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
