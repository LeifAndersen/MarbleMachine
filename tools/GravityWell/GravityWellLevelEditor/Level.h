#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsView>

class Level : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Level(QWidget *parent = 0);

    void showGrid();

signals:

public slots:

private:
    void makeGrid(int spacing);

    QVector<QPoint> gridLines;
    int gridWidth;
    int gridHeight;
    int gridSpacing;
    bool drawGrid;
};

#endif // LEVEL_H
