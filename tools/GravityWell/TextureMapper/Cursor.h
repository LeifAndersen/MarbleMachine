#ifndef CURSOR_H
#define CURSOR_H

#include <QGraphicsEllipseItem>
#include <QObject>

class Cursor : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Cursor();

signals:

public slots:

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

};

#endif // CURSOR_H
