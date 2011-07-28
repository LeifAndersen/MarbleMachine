#ifndef MAPPER_H
#define MAPPER_H

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

private:
    QComboBox * cursorSelect;
    TextureField * texturefield;

    std::vector<Cursor *> cursors;

};

#endif // MAPPER_H
