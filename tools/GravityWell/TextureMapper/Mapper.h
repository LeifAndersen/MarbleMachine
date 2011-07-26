#ifndef MAPPER_H
#define MAPPER_H

#include <QtGui/QWidget>

class Mapper : public QWidget
{
    Q_OBJECT

public:
    Mapper(QWidget *parent = 0);
    ~Mapper();
};

#endif // MAPPER_H
