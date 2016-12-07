#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <service.h>
#include <QTime>
#include <tabledlg.h>
namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    Server(int nPort, QWidget *parent = 0);
    ~Server();
private:
    QString systemCheck(QString str);
    Ui::Server *ui;
    Validator *m_ctrlValidator;
    Calculator *m_ctrlCalculator;
   // QVector<Controller*> p;
    QMessageBox *m_msgHelper;
    QTcpServer* m_ptcpServer;
    quint16 m_nNextBlockSize=0;
    QString m_lastCData="";
    TableDlg *m_tableForm;
public slots:

    void onCommand(QString cmd);
    virtual void slotNewConnection();
    void slotReadClient();
    void sendToClient(const QString &str, QTcpSocket *pSocket );
private slots:
    void on_actionHelp_triggered();
    void on_actionAbout_the_program_triggered();
signals:
    void sendTableData(int, QString, QString, int);
};

#endif // SERVER_H
