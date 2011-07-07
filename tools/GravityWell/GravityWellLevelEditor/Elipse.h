#ifndef ELIPSE_H
#define ELIPSE_H

#include <QGraphicsEllipseItem>

#include "LevelObject.h"

class Elipse : public QObject, public QGraphicsEllipseItem, public LevelObject
{
public:
    Elipse(unsigned long id);

signals:

public slots:

};

#endif // ELIPSE_H
