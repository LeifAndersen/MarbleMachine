#include "Mapper.h"

Mapper::Mapper(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout * gridLayout = new QGridLayout;

    gridLayout->setSpacing(5);

    texturefield = new TextureField(this);
    texturefield->setMinimumHeight(500);
    texturefield->setMinimumWidth(500);
    connect(this, SIGNAL(newTexture(QPixmap *)), texturefield, SLOT(newTexture(QPixmap *)));
    gridLayout->addWidget(texturefield, 0, 2, 10, 1);


    // Controls
    QPushButton * openTextureButton = new QPushButton("Open\nTexture");
    openTextureButton->setMaximumSize(110,50);
    openTextureButton->setMinimumSize(110,50);
    connect(openTextureButton, SIGNAL(clicked()), this, SLOT(openTexture()));
    gridLayout->addWidget(openTextureButton, 0, 0, Qt::AlignCenter);

    //

    QPushButton * saveCoordinatesButton = new QPushButton("Save\nCoordinates");
    saveCoordinatesButton->setMaximumSize(110,50);
    saveCoordinatesButton->setMinimumSize(110,50);
    connect(saveCoordinatesButton, SIGNAL(clicked()), this, SLOT(saveCoordinates()));
    gridLayout->addWidget(saveCoordinatesButton, 0, 1, Qt::AlignCenter);

    //

    QPushButton * addCursorButton = new QPushButton("Add\nCursor");
    addCursorButton->setMaximumSize(110,50);
    addCursorButton->setMinimumSize(110,50);
    connect(addCursorButton, SIGNAL(clicked()), this, SLOT(addCursor()));
    gridLayout->addWidget(addCursorButton, 1, 0, Qt::AlignCenter);

    //

    QPushButton * removeCursorButton = new QPushButton("Remove\nCursor");
    removeCursorButton->setMaximumSize(110,50);
    removeCursorButton->setMinimumSize(110,50);
    connect(removeCursorButton, SIGNAL(clicked()), this, SLOT(removeCursor()));
    gridLayout->addWidget(removeCursorButton, 1, 1, Qt::AlignCenter);

    //

    QIntValidator * iValid = new QIntValidator(0);

    QLineEdit * xPosEdit = new QLineEdit();
    xPosEdit->setValidator(iValid);
    xPosEdit->setMaximumWidth(100);
    connect(xPosEdit, SIGNAL(textEdited(QString)), this, SLOT(setXPos(QString)));
    gridLayout->addWidget(xPosEdit, 3, 1, Qt::AlignCenter);

    QLabel * xPosLabel = new QLabel("X Position");
    gridLayout->addWidget(xPosLabel, 3, 0, Qt::AlignCenter);

    //

    QLineEdit * yPosEdit = new QLineEdit();
    yPosEdit->setValidator(iValid);
    yPosEdit->setMaximumWidth(100);
    connect(yPosEdit, SIGNAL(textEdited(QString)), this, SLOT(setYPos(QString)));
    gridLayout->addWidget(yPosEdit, 4, 1, Qt::AlignCenter);

    QLabel * yPosLabel = new QLabel("Y Position");
    gridLayout->addWidget(yPosLabel, 4, 0, Qt::AlignCenter);

    //

    cursorSelect = new QComboBox();
    connect(cursorSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(cursorChanged(int)));
    gridLayout->addWidget(cursorSelect, 2, 1, Qt::AlignCenter);

    QLabel * cursorSelectLabel = new QLabel("Current Cursor");
    gridLayout->addWidget(cursorSelectLabel, 2, 0, Qt::AlignCenter);

    setLayout(gridLayout);
}

Mapper::~Mapper()
{

}

// Used to generate a unique identifier
unsigned long makeId() {
    static unsigned long nextId = 0;
    return ++nextId;
}

void Mapper::openTexture() {
    QString fname = QFileDialog::getOpenFileName(this, tr("Open Texture"),
                                                        "",
                                                        tr("Images (*.bmp *.gif *.jpg *.jpeg *.png)"));
    if (!fname.isNull()) {
        // File Opened Successfully
        QPixmap * texture = new QPixmap(fname);
        emit newTexture(texture);
    }
}

void Mapper::saveCoordinates() {
    // TODO -- understand the format and get to a point where there is data to be saved.
}

void Mapper::addCursor() {

}

void Mapper::removeCursor() {

}

void Mapper::setXPos(QString xPos) {

}

void Mapper::setXPos(int xPos) {

}

void Mapper::setYPos(QString yPos) {

}

void Mapper::setYPos(int yPos) {

}

void Mapper::cursorChanged(int selection) {

}
