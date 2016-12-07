#include <console.h>
#include <QTextBlock>
#include <QScrollBar>
#include <client.h>
Console::Console(QWidget *parent): QPlainTextEdit(parent){
    prompt="$ ";
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::white);
    setPalette(p);

    history = new QStringList;
    historyPos = 0;
    insertPrompt(false);
    isLocked = false;
}

Console::~Console()
{

}
void Console::scrollDown()
{
    QScrollBar *vbar = verticalScrollBar();
    vbar->setValue(vbar->maximum());
}
void Console::insertPrompt(bool insertNewBlock)
{
    QTextCharFormat format;
    format.setForeground(Qt::white);
    textCursor().setBlockCharFormat(format);
    if(insertNewBlock)
        textCursor().insertBlock();
    textCursor().insertText(prompt);
    scrollDown();
}

void Console::onEnter()
{
    if(textCursor().positionInBlock() == prompt.length())
    {
        insertPrompt(true);
        return;
    }
    QString cmd = textCursor().block().text().mid(prompt.length());
    historyAdd(cmd);

    isLocked = true;
    emit onCommand(cmd);
}
void Console::historyAdd(QString cmd)
{
    history->append(cmd);
    historyPos = history->length();
}
void Console::historyBack()
{
    if(!historyPos)
        return;
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.insertText(prompt + history->at(historyPos-1));
    setTextCursor(cursor);
    historyPos--;
}
void Console::historyForward()
{
    if(historyPos == history->length())
        return;
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    if(historyPos == history->length() - 1)
        cursor.insertText(prompt);
    else
        cursor.insertText(prompt + history->at(historyPos + 1));
    setTextCursor(cursor);
    historyPos++;
}
void Console::output(QString s)
{
    QTextCharFormat format;
    format.setForeground(Qt::white);
    textCursor().setBlockCharFormat(format);
    textCursor().insertBlock();
    textCursor().insertText(s);
    insertPrompt();
    isLocked = false;
}
void Console::mouseDoubleClickEvent(QMouseEvent* event){

}
void Console::mousePressEvent(QMouseEvent* event){
    setFocus();
}

void Console::contextMenuEvent(QContextMenuEvent* event){

}

void Console::keyPressEvent(QKeyEvent* event){
    if(isLocked)
            return;
    if(event->key() >= 0x20 && event->key() <= 0x7e
         && (event->modifiers() == Qt::NoModifier || event->modifiers() == Qt::ShiftModifier))
          QPlainTextEdit::keyPressEvent(event);
    if(event->key() == Qt::Key_Backspace
           && event->modifiers() == Qt::NoModifier
           && textCursor().positionInBlock() > prompt.length())
            QPlainTextEdit::keyPressEvent(event);
    if(event->key() == Qt::Key_Return && event->modifiers() == Qt::NoModifier)
           onEnter();
    if(event->key() == Qt::Key_Up && event->modifiers() == Qt::NoModifier)
            historyBack();
        if(event->key() == Qt::Key_Down && event->modifiers() == Qt::NoModifier)
            historyForward();
}

