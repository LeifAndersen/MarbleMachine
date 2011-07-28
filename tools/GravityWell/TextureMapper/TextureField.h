#ifndef TEXTUREFIELD_H
#define TEXTUREFIELD_H

#include <QGraphicsView>

class TextureField : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TextureField(QWidget *parent = 0);

signals:

public slots:
    void newTexture(QPixmap *);

};

#endif // TEXTUREFIELD_H
