#include <QBrush>
#include <QPen>

#include <math.h>

#include "Elipse.h"

Elipse::Elipse(unsigned long id, QColor color, double x, double y, double xv, double yv, double m) : LevelObject(id) {
    QBrush brush;
    QPen pen;

    brush.setColor(color);
    xPos = x;
    yPos = y;
    velocity.x = xv;
    velocity.y = yv;
    mass = m;
    radius = log10(abs(m));
    pen.setWidth(ceil((double)radius / 5));
    // Outline color
    m < 0 ? pen.setColor(Qt::black) : pen.setColor(Qt::white);

    this->setBrush(brush);
    this->setPen(pen);
}
