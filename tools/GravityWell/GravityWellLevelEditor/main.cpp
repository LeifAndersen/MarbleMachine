#include <QtGui/QApplication>
#include "Editor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Editor w;
    w.setWindowTitle("GravityWell Level Editor v0.1.5");
    w.show();

    return a.exec();
}
