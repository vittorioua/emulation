/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

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

class Ui_Client
{
public:
    QWidget *centralWidget;
    Console *plainTextEdit;
    QMenuBar *menuBar;
    QMenu *menuInfo;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QStringLiteral("Client"));
        Client->resize(510, 120);
        Client->setMinimumSize(QSize(510, 120));
        Client->setMaximumSize(QSize(510, 120));
        Client->setAutoFillBackground(true);
        Client->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(Client);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAutoFillBackground(true);
        plainTextEdit = new Console(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(0, 0, 511, 99));
        plainTextEdit->setMinimumSize(QSize(511, 99));
        plainTextEdit->setMaximumSize(QSize(16777215, 99));
        plainTextEdit->setStyleSheet(QStringLiteral("border: 0px;"));
        Client->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Client);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 510, 20));
        menuInfo = new QMenu(menuBar);
        menuInfo->setObjectName(QStringLiteral("menuInfo"));
        Client->setMenuBar(menuBar);

        menuBar->addAction(menuInfo->menuAction());

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "Client", 0));
        menuInfo->setTitle(QApplication::translate("Client", "Info", 0));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
