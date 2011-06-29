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

#include "Editor.h"

Editor::Editor(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout * gridLayout = new QGridLayout;

    gridLayout->setSpacing(5);

    // Put the level in the editor
    level = new Level(this);
    level->setMinimumHeight(480);
    level->setMinimumWidth(854);
    gridLayout->addWidget(level, 2, 0, 1, 7);

    // Item controls.  These can be used to edit the item about to be created and in the future,
    // the selected item.
    QPushButton * addButton = new QPushButton("+");
    connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
    gridLayout->addWidget(addButton, 0, 0, Qt::AlignCenter);

    QLabel * addLabel = new QLabel("Add Item");
    gridLayout->addWidget(addLabel, 1, 0, Qt::AlignCenter);

    //

    QComboBox * itemSelect = new QComboBox();
    connect(addButton, SIGNAL(currentIndexChanged(int)), level, SLOT(changeItem(int)));
    gridLayout->addWidget(itemSelect, 0, 1, Qt::AlignCenter);

    QLabel * selectLabel = new QLabel("Select Item to Add");
    gridLayout->addWidget(selectLabel, 1, 1, Qt::AlignCenter);

    //

    QDoubleValidator * dValid = new QDoubleValidator(0);

    QLineEdit * xPosEdit = new QLineEdit();
    xPosEdit->setValidator(dValid);
    xPosEdit->setMaximumWidth(100);
    connect(xPosEdit, SIGNAL(textEdited(QString)), this, SLOT(setXPos(QString)));
    gridLayout->addWidget(xPosEdit, 0, 2, Qt::AlignCenter);

    QLabel * xPosLabel = new QLabel("X Position");
    gridLayout->addWidget(xPosLabel, 1, 2, Qt::AlignCenter);

    //

    QLineEdit * yPosEdit = new QLineEdit();
    yPosEdit->setValidator(dValid);
    yPosEdit->setMaximumWidth(100);
    connect(yPosEdit, SIGNAL(textEdited(QString)), this, SLOT(setYPos(QString)));
    gridLayout->addWidget(yPosEdit, 0, 3, Qt::AlignCenter);

    QLabel * yPosLabel = new QLabel("Y Position");
    gridLayout->addWidget(yPosLabel, 1, 3, Qt::AlignCenter);

    //

    QLineEdit * xVelEdit = new QLineEdit();
    xVelEdit->setValidator(dValid);
    xVelEdit->setMaximumWidth(100);
    connect(xVelEdit, SIGNAL(textEdited(QString)), this, SLOT(setXVel(QString)));
    gridLayout->addWidget(xVelEdit, 0, 4, Qt::AlignCenter);

    QLabel * xVelLabel = new QLabel("X Velocity");
    gridLayout->addWidget(xVelLabel, 1, 4, Qt::AlignCenter);

    //

    QLineEdit * yVelEdit = new QLineEdit();
    yVelEdit->setValidator(dValid);
    yVelEdit->setMaximumWidth(100);
    connect(yVelEdit, SIGNAL(textEdited(QString)), this, SLOT(setYVel(QString)));
    gridLayout->addWidget(yVelEdit, 0, 5, Qt::AlignCenter);

    QLabel * yVelLabel = new QLabel("Y Velocity");
    gridLayout->addWidget(yVelLabel, 1, 5, Qt::AlignCenter);

    //

    QLineEdit * massEdit = new QLineEdit();
    massEdit->setValidator(dValid);
    massEdit->setMaximumWidth(100);
    connect(massEdit, SIGNAL(textEdited(QString)), this, SLOT(setMass(QString)));
    gridLayout->addWidget(massEdit, 0, 6, Qt::AlignCenter);

    QLabel * massLabel = new QLabel("Edit Mass");
    gridLayout->addWidget(massLabel, 1, 6, Qt::AlignCenter);

    // Editing options

    // Show Grid
    QCheckBox * showGridCheckBox = new QCheckBox("Show Grid", this);
    showGridCheckBox->setCheckState(Qt::Checked);
    connect(showGridCheckBox, SIGNAL(toggled(bool)), level, SLOT(showGrid(bool)));
    gridLayout->addWidget(showGridCheckBox, 3, 0, Qt::AlignCenter);

    // Snap to grid
    QCheckBox * snapToGridCheckBox = new QCheckBox("Snap To Grid", this);
    snapToGridCheckBox->setCheckState(Qt::Checked);
    connect(snapToGridCheckBox, SIGNAL(toggled(bool)), level, SLOT(snapTo(bool)));
    gridLayout->addWidget(snapToGridCheckBox, 3, 1, Qt::AlignCenter);

    setLayout(gridLayout);

    level->showGrid();
}

Editor::~Editor()
{

}
