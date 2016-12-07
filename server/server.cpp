#include "server.h"
#include "ui_server.h"
#include <QTime>
#include <service.h>
#include <QMessageBox>
#include <QProcess>
#include <console.h>
#include <tabledlg.h>
Server::Server(int nPort, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    m_ctrlValidator=new Validator();
    m_ctrlCalculator=new Calculator();
   // p.push_back(m_ctrlCalculator);
    m_msgHelper=new QMessageBox();
    m_msgHelper->addButton(QMessageBox::Yes);
    m_msgHelper->addButton(QMessageBox::No);
    m_ptcpServer=new QTcpServer(this);
    if(!m_ptcpServer->listen(QHostAddress::Any,nPort)){
        QMessageBox::critical(0,"Server Error","Unable to start the server: "+m_ptcpServer->errorString());
        m_ptcpServer->close();
        return;
    }
    m_tableForm=new TableDlg(this);
    connect(m_ptcpServer,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
    connect(ui->console, SIGNAL(onCommand(QString)), this, SLOT(onCommand(QString)));
    connect(this, SIGNAL(sendTableData(QStringList)), m_tableForm, SLOT(getTableData(QStringList)));
}

Server::~Server()
{
    delete ui;
}

QString Server::systemCheck(QString str)
{

    if(str.length()==0){
        return "Server Response: Received Error - empty string.";
    }
   /* //sendToClient("Server Response: Received \""+str+"\"",pClientSocket);
    //
    //block of validation and separation
    if(m_ctrlValidator->readyToWork()){
        if(m_ctrlValidator->separate(str)){
            //QMessageBox::critical(0,"Message","1",QMessageBox::Ok);
            ui->textEdit->append(m_ctrlValidator->getCmdData().first);
            for(int i=0; m_ctrlValidator->getCmdData().second[i]!=NULL; i++){
               ui->textEdit->append(QString::number(m_ctrlValidator->getCmdData().second[i]));
            }
        }else{
            //QMessageBox::critical(0,"Message","Failed",QMessageBox::Ok);
        }
    }*/
    //*/
    //block of command checking
    if(str=="RFSFS")
    {
        m_msgHelper->setWindowTitle("ATTENTION!");
        m_msgHelper->setText("Request for starting the flight simulation was received.\nRequired confirm.");
        if(m_msgHelper->exec()==QMessageBox::Yes){
            return "RFSFS - was allowed.";
        }else{
            return "RFSFS - was refused.";
        }
    }else{
        if(str=="RFTDS"){
            m_tableForm->show();
            return "Success!";
        }else{
            if(str=="RFTDH"){
                m_tableForm->hide();
                return "Success!";
            }else{
                if(str.contains("$FD$")){
                    //return str;
                    if(m_ctrlValidator->separate(str))  emit sendTableData(m_ctrlValidator->getCmdData());
                    else return "Error: Data separation fault";
                }else{
                    return "Error: Command not found.";
                }
            }
        }
    }

}

void Server::sendToClient(const QString &str, QTcpSocket *pSocket)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    out<<quint16(0)<<QTime::currentTime()<<str;
    out.device()->seek(0);
    out<<quint16(arrBlock.size()-sizeof(quint16));
    pSocket->write(arrBlock);
}

void Server::slotNewConnection()
{
    QTcpSocket* pClientSocket=m_ptcpServer->nextPendingConnection();
    connect(pClientSocket,SIGNAL(disconnected()),pClientSocket,SLOT(deleteLater()));
    connect(pClientSocket,SIGNAL(readyRead()),this,SLOT(slotReadClient()));
    sendToClient("Server Response: Connected!",pClientSocket);
}

void Server::slotReadClient()
{

    QTcpSocket* pClientSocket=(QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_2);
    for(;;){
        if(!m_nNextBlockSize){
            if(pClientSocket->bytesAvailable()<sizeof(quint16)){
                break;
            }
            in>>m_nNextBlockSize;
        }
        if(pClientSocket->bytesAvailable()<m_nNextBlockSize){
            break;
        }
        QTime time;
        QString str;
        in>>time>>str;
        if(!str.contains("$FD$")){
            QString strMessage=time.toString()+" Client has sent: "+str;
            ui->console->output(strMessage);
        }
        //ui->textEdit->append(strMessage);
        sendToClient(systemCheck(str),pClientSocket);
        m_nNextBlockSize=0;
        //
    }
}

void Server::onCommand(QString cmd)
{
    m_lastCData="null";
    if(!m_ctrlValidator->findOperation(cmd))
        ui->console->output("\""+cmd+"\" не является внутренней или внешней командой.");
    else{
        m_lastCData=cmd;
        ui->console->output(systemCheck(m_lastCData));
    }
}

void Server::on_actionHelp_triggered()
{
    QProcess* proc=new QProcess(this);
    proc->start("notepad Help.txt");
}

void Server::on_actionAbout_the_program_triggered()
{
    QMessageBox::information(0,"About","Server: Version 0.1. \nTechnoligies: TcpSockets", QMessageBox::Ok);
}
