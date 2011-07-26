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

    QLineEdit * x1PosEdit = new QLineEdit();
    x1PosEdit->setValidator(iValid);
    x1PosEdit->setMaximumWidth(100);
    connect(x1PosEdit, SIGNAL(textEdited(QString)), this, SLOT(setX1Pos(QString)));
    gridLayout->addWidget(x1PosEdit, 0, 2, Qt::AlignCenter);

    QLabel * xPosLabel = new QLabel("X1 Position");
    gridLayout->addWidget(xPosLabel, 1, 2, Qt::AlignCenter);

    //

    QLineEdit * y1PosEdit = new QLineEdit();
    y1PosEdit->setValidator(iValid);
    y1PosEdit->setMaximumWidth(100);
    connect(y1PosEdit, SIGNAL(textEdited(QString)), this, SLOT(setY1Pos(QString)));
    gridLayout->addWidget(y1PosEdit, 0, 3, Qt::AlignCenter);

    QLabel * yPosLabel = new QLabel("Y1 Position");
    gridLayout->addWidget(yPosLabel, 1, 3, Qt::AlignCenter);

    //

    QLineEdit * x2PosEdit = new QLineEdit();
    x2PosEdit->setValidator(iValid);
    x2PosEdit->setMaximumWidth(100);
    connect(x2PosEdit, SIGNAL(textEdited(QString)), this, SLOT(setX2Pos(QString)));
    gridLayout->addWidget(x2PosEdit, 0, 4, Qt::AlignCenter);

    QLabel * x2PosLabel = new QLabel("X2 Position");
    gridLayout->addWidget(x2PosLabel, 1, 4, Qt::AlignCenter);

    //

    QLineEdit * y2PosEdit = new QLineEdit();
    y2PosEdit->setValidator(iValid);
    y2PosEdit->setMaximumWidth(100);
    connect(y2PosEdit, SIGNAL(textEdited(QString)), this, SLOT(setY2Pos(QString)));
    gridLayout->addWidget(y2PosEdit, 0, 5, Qt::AlignCenter);

    QLabel * y2PosLabel = new QLabel("Y2 Position");
    gridLayout->addWidget(y2PosLabel, 1, 5, Qt::AlignCenter);

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
