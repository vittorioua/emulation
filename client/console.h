#ifndef CONSOLE
#define CONSOLE

#include <QPlainTextEdit>

class Console: public QPlainTextEdit{
    Q_OBJECT
public:

    explicit Console(QWidget *parent=0);
    ~Console();
    void output(QString);
    void scrollDown();
protected:
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void contextMenuEvent(QContextMenuEvent *);
private:
    QString prompt;
    bool isLocked;
    QStringList *history;
    int historyPos;

    void onEnter();
    void insertPrompt(bool insertNewBlock = true);
    void historyAdd(QString);
    void historyBack();
    void historyForward();
signals:
    void onCommand(QString);

};

#endif // CONSOLE

