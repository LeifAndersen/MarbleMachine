#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include <QGraphicsPixmapItem>

#include "LevelObject.h"

class Image : public QObject, public QGraphicsPixmapItem, public LevelObject
{
public:
    Image(unsigned long id);

signals:

public slots:

private:
    std::string resourcePath;

};

#endif // IMAGE_H
