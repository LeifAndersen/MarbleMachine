#include "Level.h"

Level::Level(int width, int height, QWidget *parent) :
    QGraphicsView(parent)
{
    // Set the size of the scene.
    setScene(new QGraphicsScene(0, 0, width, height, this));

    setRenderHints(QPainter::SmoothPixmapTransform);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::NoViewportUpdate);

    setPalette(QPalette(QColor(0, 0, 0)));
    setAutoFillBackground(true);
    this->show();

    gridSpacing = 10;
}

void Level::makeGrid(int spacing) {
    for (int i = spacing; i < gridWidth; i += spacing) {
        gridLines.push_back(QPoint(i, 0));
        gridLines.push_back(QPoint(i, gridHeight));
    }
    for (int i = spacing; i < gridHeight; i += spacing) {
        gridLines.push_back(QPoint(i, 0));
        gridLines.push_back(QPoint(i, gridWidth));
    }

}

void Level::showGrid(bool show) {
    if(gridWidth != width() && gridHeight != height()) {
        gridWidth = width();
        gridHeight = height();
        makeGrid(gridSpacing);
    }

    // Draw Grid
    drawGrid = show;

    // TODO -- actually draw teh gridz
}

void Level::snapTo(bool) {
    // TODO -- care about this feature.
}

void Level::addElipseItem(Elipse * elipse) {
    objects.push_back(elipse);
    scene()->addItem(elipse);
    scene()->update();
}

void Level::addImageItem(Image * image) {
    // TODO -- need pixmap items
}
