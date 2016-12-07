#include "client.h"
#include <QApplication>
#include <glut.h>
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    QApplication a(argc, argv);
    Client w("localhost",7676);
    w.show();

    return a.exec();
}
