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
};

#endif // EDITOR_H
