#ifndef SERVICE
#define SERVICE
#include <QMainWindow>
#include <QSet>
#include <QPair>
#include <QRegExp>

class Controller
{
protected:
    bool status=false;
public:
    bool readyToWork();
    Controller();
    ~Controller();
};

/*class Converter: public Controller
{
public:
    Converter();
    ~Converter();
    QPair<QString, QVector<double>> dataSeparation(QString str);
    QString dataUnity(QString str, QVector<double>);
protected:
};

class Validator: public Controller
{
public:
    Validator();
    ~Validator();
    bool operationCheck();
    bool dataCheck();
private:
    Controller *m_ctrlConverter;
    QSet<QString> m_opEnum;
protected:
    QPair<QString, QVector<double>> m_cmdData;
};*/

class Converter: public Controller
{
public:
    Converter();
    ~Converter();
protected:
    QPair<QString, double*> dataSeparation(QString str);
    QString dataUnity(QPair<QString, double*> data);
    QRegExp *m_sprtTemplate;
};

class Validator: public Converter
{
public:
    Validator();
    ~Validator();
    bool operationCheck();
    bool dataCheck();
    bool separate(QString cmd);
    bool unity();
    QString getCmdUnity();
    QPair<QString, double *> getCmdData();
    void setCmdUnity(QString obj);
    void setCmdData(QPair<QString, double *> obj);
    int findOperation(QString str); //1
private:
    QRegExp *m_cmdTemplate;
    QVector<QString> m_opEnum;
    QString m_cmdUnity;
    QPair<QString, double*> m_cmdData;
};
class Calculator: public Controller
{
public:
    Calculator();
    ~Calculator();
protected:
};

#endif // SERVICE

