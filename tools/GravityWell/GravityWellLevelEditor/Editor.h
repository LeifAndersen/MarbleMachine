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

public slots:
    void add();
    void changeItem(int);
    void setXPos(QString);
    void setYPos(QString);
    void setXVel(QString);
    void setYVel(QString);
    void setMass(QString);
    void setLevelName(QString);
private:
    // fields for holding object data
    double xVel;
    double yVel;
    double xPos;
    double yPos;
    double mass;
    int currentItem;
    QString levelName;


};

#endif // EDITOR_H
