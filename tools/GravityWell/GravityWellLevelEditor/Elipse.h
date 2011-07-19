#ifndef ELIPSE_H
#define ELIPSE_H

#include <QGraphicsEllipseItem>

#include "LevelObject.h"

class Elipse : public QObject, public QGraphicsEllipseItem, public LevelObject
{
    Q_OBJECT;
public:
    Elipse(unsigned long id, int type, QColor color, double xPosition, double yPosition, double xVelocity,
           double yVelocity, double mass);

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
