#include <service.h>
#include <QTextStream>
#include <QMessageBox>
bool Controller::readyToWork()
{
    return this->status;
}

Controller::Controller()
{
    this->status=true;
}

Controller::~Controller()
{

}

Converter::Converter()
{
    m_sprtTemplate=new QRegExp("(\t)|(\s)|(\,)|(\;)");
}

Converter::~Converter()
{
    delete m_sprtTemplate;
}

QPair<QString, double*> Converter::dataSeparation(QString str)
{
    QString resultStr;
    double *resultMass;
    int count=0, i=0;
    QStringList tmp =str.split(QRegExp("\\s+|\\,"),QString::SkipEmptyParts);
    for(auto var: tmp){
        if(var.toDouble()){
            count++;
        }else{
            resultStr=var;
        }
    }
    resultMass=new double[count+1];
    for(auto var: tmp){
        if(var.toDouble()){
            if(i<count){
                resultMass[i]=var.toDouble();
            }
            i++;
        }
    }
    resultMass[count]=NULL;
    return qMakePair(resultStr,resultMass);
}

QString Converter::dataUnity(QPair<QString, double*> data)
{
    QTextStream resultStr;
    resultStr<<data.first;
    int i=0;
    for(;;){
        if(data.second==NULL)
            break;
        resultStr<<" "<<data.second[i];
        i++;
    }
    return *resultStr.string();
}

Validator::Validator()
{
    //http://regexr.com/
    this->m_cmdTemplate=new QRegExp("^\-[a-z](\s[0-9]{1,}\.[0-9]{1,})+$");
    this->m_opEnum.push_back("RFSFS");
    this->m_opEnum.push_back("RFESD");
    this->m_opEnum.push_back("RFNCG");
    this->m_opEnum.push_back("Y");
    this->m_opEnum.push_back("N");
    this->m_opEnum.push_back("RFTDS");
    this->m_opEnum.push_back("RFTDH");
   /* this->m_ctrlConverter=new Converter();
    if(m_ctrlConverter->readyToWork()){

    }*/
}

Validator::~Validator()
{
    //delete m_ctrlConverter;
    delete this->m_cmdData.second;
    delete this->m_cmdTemplate;
}

bool Validator::operationCheck()
{
    if(this->readyToWork()){

    }
    return false;
}

bool Validator::dataCheck()
{
    if(this->readyToWork()){

    }
    return false;
}

QString Validator::getCmdUnity()
{
    return this->m_cmdUnity;
}

QPair<QString, double *> Validator::getCmdData()
{
    return this->m_cmdData;
}

void Validator::setCmdUnity(QString obj)
{
    this->m_cmdUnity=obj;
}

void Validator::setCmdData(QPair<QString, double *> obj)
{
    this->m_cmdData=obj;
}

int Validator::findOperation(QString str)
{
    for(auto var: m_opEnum){
        if(str==var) return 1;
    }
    return 0;
}

bool Validator::separate(QString cmd)
{
    if(m_cmdTemplate->exactMatch(cmd)){
 //   if(cmd.contains(*m_cmdTemplate)){
        setCmdData(dataSeparation(cmd));
        return true;
    }
    //QMessageBox::critical(0,"adw","false2",QMessageBox::Ok);
    return false;
}

bool Validator::unity()
{
    if(this->readyToWork()){
        setCmdUnity(dataUnity(getCmdData()));
        return true;
    }
    return false;
}

Calculator::Calculator()
{

}

Calculator::~Calculator()
{

}
