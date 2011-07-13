#include "Image.h"

Image::Image(unsigned long id, std::string resource) : LevelObject(id) {
    setCacheMode(QGraphicsItem::ItemCoordinateCache);

    setFlag(QGraphicsItem::ItemIsSelectable);

    setPixmap(QPixmap(resource.c_str()));
}
