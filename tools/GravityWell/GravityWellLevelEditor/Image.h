#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include <QGraphicsPixmapItem>

#include "LevelObject.h"

class Image : public QObject, public QGraphicsPixmapItem, public LevelObject
{
public:
    Image(unsigned long id, std::string resourcePath);

signals:

public slots:

private:


};

#endif // IMAGE_H
