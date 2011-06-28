#include <QtGui/QApplication>
#include "editor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Editor w;
    w.setWindowTitle("GravityWell Level Editor v0.1");
    w.show();

    return a.exec();
}
