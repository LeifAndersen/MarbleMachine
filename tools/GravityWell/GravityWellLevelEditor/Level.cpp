#include "Level.h"

Level::Level(int width, int height, QWidget *parent) :
        QGraphicsView(parent)
{
    // Set the size of the scene.
    setScene(new QGraphicsScene(0, 0, width, height, this));

    setRenderHints(QPainter::SmoothPixmapTransform);
    setRenderHints(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    //setViewportUpdateMode(QGraphicsView::NoViewportUpdate);

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

void Level::setLevelName(QString name) {
    levelName = name;
}

void Level::exportLevel(const std::vector<std::string> & itemTypes) {
    QString saveFileName = QFileDialog::getSaveFileName(this, tr("Export Level"),
                                                        "untitled.lvl",
                                                        tr("Level File (*.lvl)"));
    // Open a filestream for the output
    std::ofstream output (saveFileName.toStdString().c_str());

    if (output.good()) {
        output << "name" << levelName.toStdString() << std::endl;

        for (std::vector<LevelObject *>::iterator i = objects.begin(); i != objects.end(); i++) {
            output << itemTypes.at((*i)->type) << ":"
                    << boost::lexical_cast<std::string>((*i)->xPos) << ","
                    << boost::lexical_cast<std::string>((*i)->yPos) << ";"
                    << boost::lexical_cast<std::string>((*i)->velocity.x) << ","
                    << boost::lexical_cast<std::string>((*i)->velocity.y) << ";"
                    << boost::lexical_cast<std::string>((*i)->mass) << std::endl;
        }
        output.close();
    }
    else {
        std::cerr << "Could not write to file: " << saveFileName.toStdString() << std::endl;
        std::cerr << "Exiting" << std::endl;
    }
    return;
}
