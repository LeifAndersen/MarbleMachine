#include "Cursor.h"

Cursor::Cursor(unsigned int _id) {
    id = _id;
    this->setPixmap(QPixmap(":/crosshair"));

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

Cursor::~Cursor() {
    emit dying(this);
}

QVariant Cursor::itemChange(GraphicsItemChange change, const QVariant &value)
{
    // Catch position change
    if (change == ItemPositionHasChanged && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        emit newX(newPos.x() + radius);
        emit newY(newPos.y() + radius);
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
