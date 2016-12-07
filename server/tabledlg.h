#ifndef TABLEDLG_H
#define TABLEDLG_H

#include <QDialog>
#include <QStandardItemModel>
namespace Ui {
class TableDlg;
}

class TableDlg : public QDialog
{
    Q_OBJECT

public:
    explicit TableDlg(QWidget *parent = 0);
    ~TableDlg();
protected:
    void keyPressEvent(QKeyEvent *event);
    void saveFile(QString fileName);
public slots:
    void getTableData(QStringList obg);
private:
    int rowCounter=0;
    QStandardItemModel *m_pModel;
    Ui::TableDlg *ui;
};

#endif // TABLEDLG_H
