#ifndef CURSOR_H
#define CURSOR_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QRectF>
#include <QGraphicsScene>

class Cursor : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Cursor(unsigned int id, int width, int height);
    ~Cursor();

    unsigned int id;

signals:
    void newX(int);
    void newY(int);
    void dying(Cursor *);
    void cursorSelected(unsigned int);

public slots:

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    static const int radius = 28; // From pixmap used for cursor.

    int width;
    int height;

};

#endif // CURSOR_H
