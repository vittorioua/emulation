#ifndef CLIENT_H
#define CLIENT_H
#include <emulator.h>
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QTime>
namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    Client(const QString& strHost, int nPort, QWidget *parent = 0);

    ~Client();
public slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError err);
    void slotSendToServer(QString);
    void slotConnected();
    void onCommand(QString cmd);
private slots:

    void on_pushButton_clicked();

private:
    void systemCheck(QTime time,QString str);
    Ui::Client *ui;
    QTcpSocket *m_pTcpSocket;
    quint16 m_nNextBlockSize=0;
    Emulator *m_pEml;
    QComboBox *combo1;
    QComboBox *combo2;
    bool isStarted=false;
    Emulator emul;
};

#endif // CLIENT_H
