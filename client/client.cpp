#include "client.h"
#include "ui_client.h"
#include <QTime>
#include <emulator.h>
Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

}

Client::Client(const QString &strHost, int nPort, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    m_pTcpSocket=new QTcpSocket(this);
    m_pTcpSocket->connectToHost(strHost, nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()),SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slotError(QAbstractSocket::SocketError)));
    //connect(ui->pushButton, SIGNAL(clicked()),this,SLOT(slotSendToServer()));
    ///connect(ui->lineEdit, SIGNAL(returnPressed()),this,SLOT(slotSendToServer()));
  //  connect(ui->plainTextEdit, SIGNAL(onCommand(QString)), this, SLOT(onCommand(QString)));
    connect(ui->plainTextEdit, SIGNAL(onCommand(QString)), this, SLOT(slotSendToServer(QString)));
    connect(&emul,SIGNAL(sendFlightData(QString)),this,SLOT(slotSendToServer(QString)));
    //ui->openGLWidget->start();
    //ui->openGLWidget->show();
    //if (!isStarted) {
    //    isStarted = true;
    //    ui->openGLWidget->start();
    //}
}

Client::~Client()
{
    delete ui;
}

void Client::onCommand(QString cmd)
{
    /*QStringList response;
    //response=client->query(cmd);

    if(response.isEmpty())
    {
     ui->plainTextEdit->output("(error) empty response");
    return;
    }

    QString type=response.at(0);
    if(type=="string")
    ui->plainTextEdit->output(response.at(1));
    else if(type=="error")
    ui->plainTextEdit->output("(error) "+response.at(1));
    else if(type=="integer")
    ui->plainTextEdit->output("(integer) "+response.at(1));
    else if(type=="bulk")
    ui->plainTextEdit->output("\""+response.at(1)+"\"");
    else if(type=="list"){
    QStringList output;
    if(response.length()>1)
    {
        for(int k=1;k<response.length();k++)
        output << QString("%1").arg(k)+". \""+response.at(k)+"\"";
        ui->plainTextEdit->output(output.join("\r\n"));
    }
    else
        ui->plainTextEdit->output("empty");
    }*/
}



void Client::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_5_2);
    for(;;){
        if(!m_nNextBlockSize){
            if(m_pTcpSocket->bytesAvailable()<sizeof(quint16)){
                break;
            }
            in>>m_nNextBlockSize;
        }
        if(m_pTcpSocket->bytesAvailable()<m_nNextBlockSize){
            break;
        }
        QTime time;
        QString str;
        in>>time>>str;
        systemCheck(time,str);
        m_nNextBlockSize=0;
    }
}

void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError="Error: "+(err==QAbstractSocket::HostNotFoundError
                                ? "The host was not found." : err == QAbstractSocket::RemoteHostClosedError
                                   ? "The remote host is closed." : err == QAbstractSocket::ConnectionRefusedError
                                      ? "The connection was refused." : QString(m_pTcpSocket->errorString()));
    ui->plainTextEdit->output(strError);
}

void Client::slotSendToServer(QString cmd)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    out<<quint16(0)<<QTime::currentTime()<<cmd;

    out.device()->seek(0);
    out<<quint16(arrBlock.size()-sizeof(quint16));

    m_pTcpSocket->write(arrBlock);
    //ui->lineEdit->setText("");
    ui->plainTextEdit->scrollDown();
}

void Client::slotConnected()
{
    ui->plainTextEdit->output("Received the connected() signal");
}

void Client::on_pushButton_clicked()
{

}

void Client::systemCheck(QTime time, QString str)
{
    ui->plainTextEdit->output(""+time.toString()+" "+str);
    if (str=="RFSFS - was allowed."){
        emul.show();
        emul.resize(600, 600);
        if (!isStarted) {
            isStarted = true;
            emul.start();
        }
    }
}
