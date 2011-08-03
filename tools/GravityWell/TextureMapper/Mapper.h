#ifndef MAPPER_H
#define MAPPER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QComboBox>
#include <QFileDialog>
#include <QtGui/QWidget>

#include "TextureField.h"
#include "Cursor.h"

class Mapper : public QWidget
{
    Q_OBJECT

public:
    Mapper(QWidget *parent = 0);
    ~Mapper();

signals:
    void newTexture(QPixmap *);
    void newXText(QString);
    void newYText(QString);

public slots:
    void openTexture();
    void saveCoordinates();
    void addCursor();
    void removeCursor();
    void setXPos(QString);
    void setXPos(int);
    void setYPos(QString);
    void setYPos(int);
    void cursorChanged(int);
    void cursorDying(Cursor * dying);
    void cursorSelected(unsigned int);
    void setButtonName(QString);

private:
    QComboBox * cursorSelect;
    TextureField * texturefield;

    std::vector<Cursor *> cursors;
    unsigned int idBase;
    QString buttonName;
    QString textureFileName;

};

#endif // MAPPER_H
