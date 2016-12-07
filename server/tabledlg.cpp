#include "tabledlg.h"
#include "ui_tabledlg.h"
#include <QStandardItemModel>
#include <QFileDialog>
#include <QTextStream>
TableDlg::TableDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableDlg)
{
    ui->setupUi(this);
    m_pModel=new QStandardItemModel(10000, 4, this);
    m_pModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Flight ID"));
    m_pModel->setHeaderData(1, Qt::Horizontal, QObject::tr("From"));
    m_pModel->setHeaderData(2, Qt::Horizontal, QObject::tr("To"));
    m_pModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Time"));
    ui->tableView->setModel(m_pModel);
}

TableDlg::~TableDlg()
{
    delete ui;
}

void TableDlg::keyPressEvent(QKeyEvent *event)
{
    if ((QApplication::keyboardModifiers() & Qt::ControlModifier) &&
        (QApplication::keyboardInputInterval() & Qt::Key_S)){
         QString fileName = QFileDialog::getSaveFileName(this,
                                    QString::fromUtf8("Сохранить файл"),
                                    QDir::currentPath(),
                                    "Text (*.cvs *.txt);;All files (*.*)");
         QFile f( fileName );
         if( f.open( QIODevice::WriteOnly ) )
         {
             QTextStream ts( &f );
             QStringList strList;
             for (int i=0; i<ui->tableView->model()->rowCount(); i++)
             {
                 strList.clear();

                 for (int j=0; j<ui->tableView->model()->columnCount(); j++)
                     strList << ui->tableView->model()->data(ui->tableView->model()->index(i,j)).toString();

                 ts << strList.join("\t") + "\n";
             }
             f.close();
         }
    }
}

void TableDlg::getTableData(int number, QString from, QString to, int timer)
{

}

