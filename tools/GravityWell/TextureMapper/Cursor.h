#ifndef CURSOR_H
#define CURSOR_H

#include <QGraphicsEllipseItem>
#include <QObject>

class Cursor : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Cursor(unsigned int id);
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
    static const unsigned int radius = 28; // From pixmap used for cursor.

};

#endif // CURSOR_H
