#include <QBrush>
#include <QPen>

#include <math.h>

#include "Elipse.h"

Elipse::Elipse(unsigned long id, int type, QColor color, double x, double y, double xv, double yv, double m) : LevelObject(id, type) {
    QBrush brush;
    QPen pen;

    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    xPos = x;
    yPos = y;
    velocity.x = xv;
    velocity.y = yv;
    mass = m;
    // Radius (check for small mass)
    radius = sizeFactor * log10(abs(m));
    if (radius < 1) {
        radius = 1;
    }
    pen.setWidth(ceil((double)radius / 5));
    // Outline color
    m > 0 ? pen.setColor(Qt::black) : pen.setColor(Qt::white);

    setBrush(brush);
    setPen(pen);

    setRect(radius + x, radius + y, radius * 2, radius * 2);

    //setPos(radius * 2, radius * 2);

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

}

QVariant Elipse::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        // Update custom position fields xPos and yPos (I know this information is redundant, but
        // I want it that way for now)
        xPos = newPos.x();
        yPos = newPos.y();
    }
    return QGraphicsItem::itemChange(change, value);
}
