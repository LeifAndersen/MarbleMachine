#include "TextureField.h"

TextureField::TextureField(QWidget *parent) : QGraphicsView(parent) {
    setScene(new QGraphicsScene(0, 0, 480, 480, this));
    setRenderHints(QPainter::SmoothPixmapTransform);
    setRenderHints(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);

    this->show();
}

void TextureField::newTexture(QPixmap * texture) {

}
