#include "level.h"

Level::Level(QWidget *parent) :
    QWidget(parent)
{
    setPalette(QPalette(QColor(0, 0, 0)));
    setAutoFillBackground(true);
    this->show();
}
