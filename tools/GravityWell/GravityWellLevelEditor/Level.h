#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsView>

class Level : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Level(int width, int height, QWidget *parent = 0);

    void showGrid();

    // All the different things that can be added to a level.
    enum levelItem {
        Planet,
        AntiPlanet,
        Ship,
        AsteroidBelt
    };

signals:

public slots:
    void showGrid(bool);
    void snapTo(bool);

private:
    void makeGrid(int spacing);

    QVector<QPoint> gridLines;
    int gridWidth;
    int gridHeight;
    int gridSpacing;
    bool drawGrid;
};

#endif // LEVEL_H
