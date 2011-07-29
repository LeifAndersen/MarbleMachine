#include "Cursor.h"

Cursor::Cursor(unsigned int _id) {
    id = _id;
}

QVariant Cursor::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
    }

    return QGraphicsItem::itemChange(change, value);
}
