#include "Image.h"

Image::Image(unsigned long id, int type, std::string resource) : LevelObject(id, type) {
    setCacheMode(QGraphicsItem::ItemCoordinateCache);

    setFlag(QGraphicsItem::ItemIsSelectable);

    setPixmap(QPixmap(resource.c_str()));
}
