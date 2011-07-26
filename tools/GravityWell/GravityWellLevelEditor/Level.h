#ifndef LEVEL_H
#define LEVEL_H

#include <math.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

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
    void clear();
    void exportLevel(const std::vector<std::string> & itemTypes);

    QString filename;
    QString levelName;

signals:
    void importedLevel();

public slots:
    void showGrid(bool);
    void snapTo(bool);
    void addElipseItem(Elipse *);
    void addImageItem(Image *);
    void setLevelName(QString);
    void itemDying(Elipse *);

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
