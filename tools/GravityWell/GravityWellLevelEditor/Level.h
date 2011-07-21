#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/bimap.hpp>
#include <boost/bimap/tags/tagged.hpp>
#include <boost/lexical_cast.hpp>

#include <QGraphicsView>
#include <QFileDialog>

#include "LevelObject.h"
#include "Elipse.h"
#include "Image.h"

class Level : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Level(int width, int height, QWidget *parent = 0);

    void showGrid();

    void exportLevel(const std::vector<std::string> & itemTypes);

signals:

public slots:
    void showGrid(bool);
    void snapTo(bool);
    void addElipseItem(Elipse *);
    void addImageItem(Image *);
    void setLevelName(QString);

private:
    void makeGrid(int spacing);

    QVector<QPoint> gridLines;
    int gridWidth;
    int gridHeight;
    int gridSpacing;
    bool drawGrid;
    QString levelName;

    std::vector<LevelObject *> objects;
};

#endif // LEVEL_H
