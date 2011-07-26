#include "Elipse.h"

Elipse::Elipse(unsigned long id, int type, QColor color, double x, double y, double xv, double yv,
               double m, paintStyle style, bool isNewItem) : LevelObject(id, type) {
    QBrush brush;
    QPen pen;

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

    if (style == Solid) {
        brush.setStyle(Qt::SolidPattern);
    } else if (style == Gradient) {
        brush.setStyle(Qt::Dense1Pattern);
    } else if (style == Checkered) {
        brush.setStyle(Qt::CrossPattern);
    } else {
        // Something somewhere went terribly wrong
    }

    brush.setColor(color);


    pen.setWidth(ceil((double)radius / 5));
    // Outline color
    m > 0 ? pen.setColor(Qt::black) : pen.setColor(Qt::white);

    setBrush(brush);
    setPen(pen);

    setRect(0, 0, radius * 2, radius * 2);

    if (isNewItem) {
        setPos(x - radius, y - radius);
    } else {
        setPos(x + radius, y + radius);
    }

    //setPos(radius * 2, radius * 2);

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

}

QVariant Elipse::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        // Update custom position fields xPos and yPos (I know this information is redundant, but
        // I want it that way for now)
        xPos = newPos.x() - radius;
        std::cerr << "xPos: " << xPos << ", newPos.x()" << newPos.x() << std::endl;
        yPos = newPos.y() - radius;
        std::cerr << "yPos: " << yPos << ", newPos.y()" << newPos.y() << std::endl;
    }

    return QGraphicsItem::itemChange(change, value);
}
