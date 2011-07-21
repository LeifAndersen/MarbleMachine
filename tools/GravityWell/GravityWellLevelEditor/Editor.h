#ifndef EDITOR_H
#define EDITOR_H

#include "boost/lexical_cast.hpp"

#include <QtGui/QWidget>

#include "Level.h"

class Editor : public QWidget
{
    Q_OBJECT

public:
    Editor(QWidget *parent = 0);
    ~Editor();

    Level * level;

    struct number {};
    struct item {};
    typedef boost::bimap
            <
            boost::bimaps::tags::tagged<int, number>,
            boost::bimaps::tags::tagged<std::string, item>
            > TwoWayMap;
    typedef TwoWayMap::value_type TwoWayPair;

    // All the different things that can be added to a level.
    TwoWayMap levelItems;

signals:
    void changeItemTo(int);
    void newElipseItem(Elipse *);
    void newImageItem(Image *);

public slots:
    void add();
    void changeItem(int);
    void setXPos(QString);
    void setYPos(QString);
    void setXVel(QString);
    void setYVel(QString);
    void setMass(QString);
    void exportLevel();

private:
    // fields for holding object data
    double xVel;
    double yVel;
    double xPos;
    double yPos;
    double mass;
    int currentItem;

};

#endif // EDITOR_H
