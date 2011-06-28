#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QDial>
#include <QCheckBox>

#include "editor.h"

Editor::Editor(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout * gridLayout = new QGridLayout;

    gridLayout->setSpacing(5);

    // Put the level in the editor
    level = new Level(this);
    gridLayout->addWidget(level, 2, 0, 10, 7);

    // Item controls.  These can be used to edit the item about to be created and in the future,
    // the selected item.
    QPushButton * addButton = new QPushButton("+");
    //connect(addButton, SIGNAL(clicked()), level, SLOT(add()));
    gridLayout->addWidget(addButton, 0, 0, Qt::AlignCenter);

    QLabel * addLabel = new QLabel("Add Item");
    gridLayout->addWidget(addLabel, 1, 0, Qt::AlignCenter);

    //

    QComboBox * itemSelect = new QComboBox();
    //connect(addButton, SIGNAL(clicked()), level, SLOT(add()));
    gridLayout->addWidget(itemSelect, 0, 1, Qt::AlignCenter);

    QLabel * selectLabel = new QLabel("Select Item to Add");
    gridLayout->addWidget(selectLabel, 1, 1, Qt::AlignCenter);

    //

    QDoubleValidator * dValid = new QDoubleValidator(0);

    QLineEdit * xPosEdit = new QLineEdit();
    xPosEdit->setValidator(dValid);
    //connect(addButton, SIGNAL(clicked()), level, SLOT(add()));
    gridLayout->addWidget(xPosEdit, 0, 2, Qt::AlignCenter);

    QLabel * xPosLabel = new QLabel("X Position");
    gridLayout->addWidget(xPosLabel, 1, 2, Qt::AlignCenter);

    //

    QLineEdit * yPosEdit = new QLineEdit();
    yPosEdit->setValidator(dValid);
    //connect(addButton, SIGNAL(clicked()), level, SLOT(add()));
    gridLayout->addWidget(yPosEdit, 0, 3, Qt::AlignCenter);

    QLabel * yPosLabel = new QLabel("Y Position");
    gridLayout->addWidget(yPosLabel, 1, 3, Qt::AlignCenter);

    //

    QLineEdit * xVelEdit = new QLineEdit();
    xVelEdit->setValidator(dValid);
    //connect(addButton, SIGNAL(clicked()), level, SLOT(add()));
    gridLayout->addWidget(xVelEdit, 0, 4, Qt::AlignCenter);

    QLabel * xVelLabel = new QLabel("X Velocity");
    gridLayout->addWidget(xVelLabel, 1, 4, Qt::AlignCenter);

    //

    QLineEdit * yVelEdit = new QLineEdit();
    yVelEdit->setValidator(dValid);
    //connect(addButton, SIGNAL(clicked()), level, SLOT(add()));
    gridLayout->addWidget(yVelEdit, 0, 5, Qt::AlignCenter);

    QLabel * yVelLabel = new QLabel("Y Velocity");
    gridLayout->addWidget(yVelLabel, 1, 5, Qt::AlignCenter);

    //

    QLineEdit * massEdit = new QLineEdit();
    massEdit->setValidator(dValid);
    //connect(addButton, SIGNAL(clicked()), level, SLOT(add()));
    gridLayout->addWidget(massEdit, 0, 6, Qt::AlignCenter);

    QLabel * massLabel = new QLabel("Edit Mass");
    gridLayout->addWidget(massLabel, 1, 6, Qt::AlignCenter);

    //

    setLayout(gridLayout);
}

Editor::~Editor()
{

}
