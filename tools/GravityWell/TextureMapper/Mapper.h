#ifndef MAPPER_H
#define MAPPER_H

#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QCheckBox>
#include <QtGui/QWidget>

#include "TextureField.h"

class Mapper : public QWidget
{
    Q_OBJECT

public:
    Mapper(QWidget *parent = 0);
    ~Mapper();

signals:

public slots:

private:

    TextureField * texturefield;


};

#endif // MAPPER_H
