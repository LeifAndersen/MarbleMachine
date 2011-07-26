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
    gridLayout->addWidget(texturefield, 2, 0, 1, 7);


    // Controls
    QPushButton * openTextureButton = new QPushButton("Open Texture");
    connect(openTextureButton, SIGNAL(clicked()), this, SLOT(openTexture()));
    gridLayout->addWidget(openTextureButton, 0, 0, Qt::AlignCenter);

    //

    QPushButton * saveCoordinatesButton = new QPushButton("Save Coordinates");
    connect(saveCoordinatesButton, SIGNAL(clicked()), this, SLOT(saveCoordinates()));
    gridLayout->addWidget(saveCoordinatesButton, 0, 1, Qt::AlignCenter);

    //

    QIntValidator * iValid = new QIntValidator(0);

    QLineEdit * xPosEdit = new QLineEdit();
    xPosEdit->setValidator(iValid);
    xPosEdit->setMaximumWidth(100);
    connect(xPosEdit, SIGNAL(textEdited(QString)), this, SLOT(setXPos(QString)));
    gridLayout->addWidget(xPosEdit, 0, 2, Qt::AlignCenter);

    QLabel * xPosLabel = new QLabel("X Position");
    gridLayout->addWidget(xPosLabel, 1, 2, Qt::AlignCenter);

    //

    QLineEdit * yPosEdit = new QLineEdit();
    yPosEdit->setValidator(iValid);
    yPosEdit->setMaximumWidth(100);
    connect(yPosEdit, SIGNAL(textEdited(QString)), this, SLOT(setYPos(QString)));
    gridLayout->addWidget(yPosEdit, 0, 3, Qt::AlignCenter);

    QLabel * yPosLabel = new QLabel("Y Position");
    gridLayout->addWidget(yPosLabel, 1, 3, Qt::AlignCenter);

    //

    QLabel * cursorNumber = new QLabel("");
    gridLayout->addWidget(cursorNumber, 0, 4, Qt::AlignCenter);

    QLabel * cursorNumberLabel = new QLabel("Cursor Number");
    gridLayout->addWidget(cursorNumberLabel, 1, 4, Qt::AlignCenter);

    //

    QPushButton * addCursorButton = new QPushButton("Add Cursor");
    connect(addCursorButton, SIGNAL(clicked()), this, SLOT(addCursor()));
    gridLayout->addWidget(addCursorButton, 0, 5, Qt::AlignCenter);

    //

    QLabel * colorBox = new QLabel("");
    colorBox->setMinimumSize(50,50);
    gridLayout->addWidget(colorBox, 1, 6, Qt::AlignCenter);

    QLabel * colorBoxLabel = new QLabel("Change Cursor Color");
    gridLayout->addWidget(colorBoxLabel, 1, 6, Qt::AlignCenter);

    setLayout(gridLayout);
}

Mapper::~Mapper()
{

}
