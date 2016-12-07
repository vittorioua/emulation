/********************************************************************************
** Form generated from reading UI file 'tabledlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEDLG_H
#define UI_TABLEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_TableDlg
{
public:
    QTableView *tableView;

    void setupUi(QDialog *TableDlg)
    {
        if (TableDlg->objectName().isEmpty())
            TableDlg->setObjectName(QStringLiteral("TableDlg"));
        TableDlg->resize(461, 299);
        tableView = new QTableView(TableDlg);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(0, 0, 461, 301));
        tableView->setStyleSheet(QStringLiteral("border: 0px;"));

        retranslateUi(TableDlg);

        QMetaObject::connectSlotsByName(TableDlg);
    } // setupUi

    void retranslateUi(QDialog *TableDlg)
    {
        TableDlg->setWindowTitle(QApplication::translate("TableDlg", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class TableDlg: public Ui_TableDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEDLG_H
