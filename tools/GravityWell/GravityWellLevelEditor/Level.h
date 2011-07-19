#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <boost/bimap.hpp>
#include <boost/bimap/tags/tagged.hpp>

#include <QGraphicsView>

#include "LevelObject.h"
#include "Elipse.h"
#include "Image.h"

class Level : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Level(int width, int height, QWidget *parent = 0);

    void showGrid();

signals:

public slots:
    void showGrid(bool);
    void snapTo(bool);
    void addElipseItem(Elipse *);
    void addImageItem(Image *);

private:
    void makeGrid(int spacing);

    QVector<QPoint> gridLines;
    int gridWidth;
    int gridHeight;
    int gridSpacing;
    bool drawGrid;

    std::vector<LevelObject *> objects;
};

#endif // LEVEL_H
