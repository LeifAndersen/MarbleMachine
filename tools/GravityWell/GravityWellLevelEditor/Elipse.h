#ifndef ELIPSE_H
#define ELIPSE_H

#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>

#include <math.h>
#include <iostream>

#include "LevelObject.h"

class Elipse : public QObject, public QGraphicsEllipseItem, public LevelObject
{
    Q_OBJECT;
public:
    // Styles for painting (secretly levelItem type, but this is a better abstraction)
    enum paintStyle {
        Solid,
        Checkered,
        Gradient
    };

    Elipse(unsigned long id, int type, QColor color, double xPosition, double yPosition, double xVelocity,
           double yVelocity, double mass, paintStyle style, bool isNewItem = true);

    // Size
    double radius;

signals:

public slots:

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    static const unsigned int sizeFactor = 5;

};

#endif // ELIPSE_H
