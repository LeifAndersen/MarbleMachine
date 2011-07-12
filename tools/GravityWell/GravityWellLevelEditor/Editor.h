#ifndef EDITOR_H
#define EDITOR_H

#include <QtGui/QWidget>

#include "Level.h"

class Editor : public QWidget
{
    Q_OBJECT

public:
    Editor(QWidget *parent = 0);
    ~Editor();

    Level * level;

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
private:
    // fields for holding object data
    double xVel;
    double yVel;
    double xPos;
    double yPos;
    double mass;
    Level::levelItem currentItem;
};

#endif // EDITOR_H
