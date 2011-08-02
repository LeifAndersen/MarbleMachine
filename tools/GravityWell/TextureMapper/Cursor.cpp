#include "Cursor.h"

Cursor::Cursor(unsigned int _id, int _width, int _height) {
    id = _id;
    width = _width;
    height = _height;

    setPixmap(QPixmap(":/crosshair"));

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

Cursor::~Cursor() {
    emit dying(this);
}

QVariant Cursor::itemChange(GraphicsItemChange change, const QVariant &value)
{
    // keep inside image
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();
        rect.moveTo(0 - radius, 0 - radius);
        if (!rect.contains(newPos)) {
            // Keep the item inside the scene rect.
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
            return newPos;
        }
    }
    // Catch position change
    if (change == ItemPositionHasChanged && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        emit newX(newPos.x());
        emit newY(newPos.y());
    }

    // catch selected change
    if (change == ItemSelectedHasChanged && scene()) {
        // value is the selected state
        bool selected = value.toBool();
        if (selected) {
            emit cursorSelected(id);
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
