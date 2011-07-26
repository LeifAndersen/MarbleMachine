#include "Cursor.h"

Cursor::Cursor()
{
}

QVariant Cursor::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
    }

    return QGraphicsItem::itemChange(change, value);
}
