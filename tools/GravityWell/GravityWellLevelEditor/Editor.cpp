#include "Editor.h"

Editor::Editor(QWidget *parent)
    : QWidget(parent)
{
    // Make the initial data safe
    xVel = 0;
    yVel = 0;
    xPos = 0;
    yPos = 0;
    mass = 0;
    currentItem = 0;

    // Enumerate all the items types that can be in a level
    levelItems.insert(TwoWayPair(0, "planet"));
    levelItems.insert(TwoWayPair(1, "planet"));
    levelItems.insert(TwoWayPair(2, "ship"));
    levelItems.insert(TwoWayPair(3, "goal"));

    QGridLayout * gridLayout = new QGridLayout;

    gridLayout->setSpacing(5);

    /*
     |                      |
     |                      |
     |----------------------|
     |                      |
     |        level         |
     |                      |
     |----------------------|
     |                      |
     |                      |
     */

    // Put the level in the editor
    level = new Level(854, 480, this);
    level->setMinimumHeight(480);
    level->setMinimumWidth(854);
    connect(this, SIGNAL(newElipseItem(Elipse *)), level, SLOT(addElipseItem(Elipse *)));
    connect(this, SIGNAL(newImageItem(Image *)), level, SLOT(addImageItem(Image *)));
    gridLayout->addWidget(level, 2, 0, 1, 13);

    // Menu bar. File, Edit, View, stuff like that.
    /*
     ________________________
     |___________________ooo|
     |Menu|Bar|Goes|Here|   |
     |----+---+----+----+---|
     |                      |
    */
    // TODO -- need this feature enough to implement it.

    // Item controls.  These can be used to edit the item about to be created and in the future,
    // the selected item.
    /*
     ________________________
     |___________________ooo|
     |__|___|_|____|________|
     |       controls       |
     |----------------------|
     |                      |
     |                      |
     */
    QPushButton * addButton = new QPushButton("+");
    connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
    gridLayout->addWidget(addButton, 0, 0, Qt::AlignCenter);

    QLabel * addLabel = new QLabel("Add Item");
    gridLayout->addWidget(addLabel, 1, 0, Qt::AlignCenter);

    //

    QComboBox * itemSelect = new QComboBox();
    connect(itemSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(changeItem(int)));
    connect(this, SIGNAL(changeItemTo(int)), itemSelect, SLOT(setCurrentIndex(int)));
    gridLayout->addWidget(itemSelect, 0, 1, Qt::AlignCenter);

    // Add items to the itemSelect from the list of all items
    for (TwoWayMap::map_by<number>::const_iterator i = levelItems.by<number>().begin();
                                                       i != levelItems.by<number>().end();
                                                       i++)
    {
        itemSelect->addItem(i->get<item>().c_str(), i->get<number>());
    }

    QLabel * selectLabel = new QLabel("Select Item to Add");
    gridLayout->addWidget(selectLabel, 1, 1, Qt::AlignCenter);

    //

    QDoubleValidator * dValid = new QDoubleValidator(0);

    QLineEdit * xPosEdit = new QLineEdit();
    xPosEdit->setValidator(dValid);
    xPosEdit->setMaximumWidth(100);
    xPosEdit->setText(boost::lexical_cast<std::string>(xPos).c_str());
    connect(xPosEdit, SIGNAL(textEdited(QString)), this, SLOT(setXPos(QString)));
    gridLayout->addWidget(xPosEdit, 0, 2, Qt::AlignCenter);

    QLabel * xPosLabel = new QLabel("X Position");
    gridLayout->addWidget(xPosLabel, 1, 2, Qt::AlignCenter);

    //

    QLineEdit * yPosEdit = new QLineEdit();
    yPosEdit->setValidator(dValid);
    yPosEdit->setMaximumWidth(100);
    yPosEdit->setText(boost::lexical_cast<std::string>(yPos).c_str());
    connect(yPosEdit, SIGNAL(textEdited(QString)), this, SLOT(setYPos(QString)));
    gridLayout->addWidget(yPosEdit, 0, 3, Qt::AlignCenter);

    QLabel * yPosLabel = new QLabel("Y Position");
    gridLayout->addWidget(yPosLabel, 1, 3, Qt::AlignCenter);

    //

    QLineEdit * xVelEdit = new QLineEdit();
    xVelEdit->setValidator(dValid);
    xVelEdit->setMaximumWidth(100);
    xVelEdit->setText(boost::lexical_cast<std::string>(xVel).c_str());
    connect(xVelEdit, SIGNAL(textEdited(QString)), this, SLOT(setXVel(QString)));
    gridLayout->addWidget(xVelEdit, 0, 4, Qt::AlignCenter);

    QLabel * xVelLabel = new QLabel("X Velocity");
    gridLayout->addWidget(xVelLabel, 1, 4, Qt::AlignCenter);

    //

    QLineEdit * yVelEdit = new QLineEdit();
    yVelEdit->setValidator(dValid);
    yVelEdit->setMaximumWidth(100);
    yVelEdit->setText(boost::lexical_cast<std::string>(yVel).c_str());
    connect(yVelEdit, SIGNAL(textEdited(QString)), this, SLOT(setYVel(QString)));
    gridLayout->addWidget(yVelEdit, 0, 5, Qt::AlignCenter);

    QLabel * yVelLabel = new QLabel("Y Velocity");
    gridLayout->addWidget(yVelLabel, 1, 5, Qt::AlignCenter);

    //

    QLineEdit * massEdit = new QLineEdit();
    massEdit->setValidator(dValid);
    massEdit->setMaximumWidth(100);
    massEdit->setText(boost::lexical_cast<std::string>(mass).c_str());
    connect(massEdit, SIGNAL(textEdited(QString)), this, SLOT(setMass(QString)));
    gridLayout->addWidget(massEdit, 0, 6, Qt::AlignCenter);

    QLabel * massLabel = new QLabel("Mass");
    gridLayout->addWidget(massLabel, 1, 6, Qt::AlignCenter);

    // Editing options
    /*
     |                      |
     |                      |
     |                      |
     |----------------------|
     |       options        |
     ------------------------
     */
    /*
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
    */
    // Delete selected
    QPushButton * deleteSelectedButton = new QPushButton("Delete Selected");
    connect(deleteSelectedButton, SIGNAL(clicked()), this, SLOT(deleteSelected()));
    gridLayout->addWidget(deleteSelectedButton, 3, 0, Qt::AlignCenter);

    // Level Name
    QLineEdit * levelNameEdit = new QLineEdit();
    levelNameEdit->setMaximumWidth(200);
    connect(levelNameEdit, SIGNAL(textEdited(QString)), level, SLOT(setLevelName(QString)));
    connect(this, SIGNAL(changeLevelName(QString)), levelNameEdit, SLOT(setText(QString)));
    gridLayout->addWidget(levelNameEdit, 3, 2, Qt::AlignCenter);

    QLabel * levelNameLabel = new QLabel("Level Name:");
    gridLayout->addWidget(levelNameLabel, 3, 1, Qt::AlignRight);

    // Level properties
    QLineEdit * planetsEdit = new QLineEdit();
    planetsEdit->setMaximumWidth(50);
    gridLayout->addWidget(planetsEdit, 3, 4, Qt::AlignCenter);
    QLabel * planetLabel = new QLabel("Light:");
    gridLayout->addWidget(planetLabel, 3, 3, Qt::AlignRight);

    planetsEdit = new QLineEdit();
    planetsEdit->setMaximumWidth(50);
    gridLayout->addWidget(planetsEdit, 3, 6, Qt::AlignCenter);
    planetLabel = new QLabel("Medium:");
    gridLayout->addWidget(planetLabel, 3, 5, Qt::AlignRight);

    planetsEdit = new QLineEdit();
    planetsEdit->setMaximumWidth(50);
    gridLayout->addWidget(planetsEdit, 3, 8, Qt::AlignCenter);
    planetLabel = new QLabel("Heavy:");
    gridLayout->addWidget(planetLabel, 3, 7, Qt::AlignRight);

    planetsEdit = new QLineEdit();
    planetsEdit->setMaximumWidth(50);
    gridLayout->addWidget(planetsEdit, 3, 10, Qt::AlignCenter);
    planetLabel = new QLabel("Anti:");
    gridLayout->addWidget(planetLabel, 3, 9, Qt::AlignRight);

    // Save level
    QPushButton * exportLevelButton = new QPushButton("Save Level");
    connect(exportLevelButton, SIGNAL(clicked()), this, SLOT(exportLevel()));
    gridLayout->addWidget(exportLevelButton, 3, 12, Qt::AlignCenter);

    // open Level
    QPushButton * importLevelButton = new QPushButton("Open Level");
    connect(importLevelButton, SIGNAL(clicked()), this, SLOT(importLevel()));
    gridLayout->addWidget(importLevelButton, 3, 11, Qt::AlignCenter);

    setLayout(gridLayout);

    level->showGrid(true);
}

// Used to generate a unique identifier
unsigned long makeId() {
    static unsigned long nextId = 0;
    return ++nextId;
}

// Makes a color for debugging purposes until the color picker is added.
QColor randomColor() {
    // color brightness from 0 to 128 (means colors vary from 0-127 + brightness).
    int brightness = 75;

    return QColor(qrand() % 128 + brightness, qrand() % 128 + brightness, qrand() % 128 + brightness);
}

Editor::~Editor()
{

}

void Editor::add() {
    if (currentItem == levelItems.by<item>().at("planet")) {
        Elipse * planet = new Elipse(makeId(), levelItems.by<item>().at("planet"),
                                     randomColor(), xPos, yPos, xVel, yVel, mass, Elipse::Solid);
        connect(planet, SIGNAL(dying(Elipse*)), level, SLOT(itemDying(Elipse*)));
        emit newElipseItem(planet);
    } else if (currentItem == levelItems.by<item>().at("planet")) {
        Elipse * antiplanet = new Elipse(makeId(), levelItems.by<item>().at("planet"),
                                   randomColor(), xPos, yPos, xVel, yVel, mass, Elipse::Solid);
        connect(antiplanet, SIGNAL(dying(Elipse*)), level, SLOT(itemDying(Elipse*)));
        emit newElipseItem(antiplanet);
    } else if (currentItem == levelItems.by<item>().at("ship")) {
        Elipse * ship = new Elipse(makeId(), levelItems.by<item>().at("ship"),
                                   randomColor(), xPos, yPos, xVel, yVel, mass, Elipse::Gradient);
        connect(ship, SIGNAL(dying(Elipse*)), level, SLOT(itemDying(Elipse*)));
        emit newElipseItem(ship);
    } else if (currentItem == levelItems.by<item>().at("goal")) {
        Elipse * goal = new Elipse(makeId(), levelItems.by<item>().at("goal"),
                                   randomColor(), xPos, yPos, xVel, yVel, mass, Elipse::Checkered);
        connect(goal, SIGNAL(dying(Elipse*)), level, SLOT(itemDying(Elipse*)));
        emit newElipseItem(goal);
    } else {
        // Something somewhere went terribly wrong
    }
}

void Editor::changeItem(int itemCode) {
    currentItem = itemCode;
}

void Editor::setXPos(QString xp) {
    xPos = xp.toDouble();
}

void Editor::setYPos(QString yp) {
    yPos = yp.toDouble();
}

void Editor::setXVel(QString xv) {
    xVel = xv.toDouble();
}

void Editor::setYVel(QString yv) {
    yVel = yv.toDouble();
}

void Editor::setMass(QString m) {
    mass = m.toDouble();

    // Restrictions
    if (levelItems.by<item>().at("planet") == currentItem
        || levelItems.by<item>().at("planet") == currentItem ) {
        if (mass > 0) {
            emit changeItemTo(levelItems.by<item>().at("planet"));
        } else {
            emit changeItemTo(levelItems.by<item>().at("planet"));
        }
    }
}

void Editor::exportLevel() {
    std::vector<std::string> types;
    // Add items to the itemSelect from the list of all items
    for (TwoWayMap::map_by<number>::const_iterator i = levelItems.by<number>().begin();
                                                       i != levelItems.by<number>().end();
                                                       i++)
    {
        types.push_back(i->get<item>());
    }

    level->exportLevel(types);
}

void Editor::importLevel() {
    QString fname = QFileDialog::getOpenFileName(this, tr("Open Level"),
                                                        level->filename,
                                                        tr("Level File (*.lvl)"));

    std::ifstream input (fname.toStdString().c_str());
    std::string line;

    if (input.good()) {
        level->filename = fname;
        level->clear();
        emit changeLevelName("");
        while(getline(input, line)) {
            std::vector<std::string> splitvec;
            boost::algorithm::split(splitvec, line, boost::algorithm::is_any_of(":"));

            // All constants derive from known filetype (not magic)
            if (splitvec.front() == "planet") {
                std::vector<std::string> splitvec2;
                boost::algorithm::split(splitvec2, splitvec[1], boost::algorithm::is_any_of(",;"));
                Elipse * planet = new Elipse(makeId(), levelItems.by<item>().at("planet"),
                                             randomColor(),
                                             boost::lexical_cast<double>(splitvec2[0]),
                                             boost::lexical_cast<double>(splitvec2[1]),
                                             boost::lexical_cast<double>(splitvec2[2]),
                                             boost::lexical_cast<double>(splitvec2[3]),
                                             boost::lexical_cast<double>(splitvec2[4]),
                                             Elipse::Solid, false);
                connect(planet, SIGNAL(dying(Elipse*)), level, SLOT(itemDying(Elipse*)));
                emit newElipseItem(planet);
            } else if (splitvec.front() == "planet") {
                std::vector<std::string> splitvec2;
                boost::algorithm::split(splitvec2, splitvec[1], boost::algorithm::is_any_of(",;"));
                Elipse * antiplanet = new Elipse(makeId(), levelItems.by<item>().at("planet"),
                                             randomColor(),
                                             boost::lexical_cast<double>(splitvec2[0]),
                                             boost::lexical_cast<double>(splitvec2[1]),
                                             boost::lexical_cast<double>(splitvec2[2]),
                                             boost::lexical_cast<double>(splitvec2[3]),
                                             boost::lexical_cast<double>(splitvec2[4]),
                                             Elipse::Solid, false);
                connect(antiplanet, SIGNAL(dying(Elipse*)), level, SLOT(itemDying(Elipse*)));
                emit newElipseItem(antiplanet);
            } else if (splitvec.front() == "ship") {
                std::vector<std::string> splitvec2;
                boost::algorithm::split(splitvec2, splitvec[1], boost::algorithm::is_any_of(",;"));
                Elipse * ship = new Elipse(makeId(), levelItems.by<item>().at("ship"),
                                             randomColor(),
                                             boost::lexical_cast<double>(splitvec2[0]),
                                             boost::lexical_cast<double>(splitvec2[1]),
                                             boost::lexical_cast<double>(splitvec2[2]),
                                             boost::lexical_cast<double>(splitvec2[3]),
                                             boost::lexical_cast<double>(splitvec2[4]),
                                             Elipse::Gradient, false);
                connect(ship, SIGNAL(dying(Elipse*)), level, SLOT(itemDying(Elipse*)));
                emit newElipseItem(ship);
            } else if (splitvec.front() == "goal") {
                std::vector<std::string> splitvec2;
                boost::algorithm::split(splitvec2, splitvec[1], boost::algorithm::is_any_of(",;"));
                Elipse * goal = new Elipse(makeId(), levelItems.by<item>().at("goal"),
                                             randomColor(),
                                             boost::lexical_cast<double>(splitvec2[0]),
                                             boost::lexical_cast<double>(splitvec2[1]),
                                             boost::lexical_cast<double>(splitvec2[2]),
                                             boost::lexical_cast<double>(splitvec2[3]),
                                             boost::lexical_cast<double>(splitvec2[4]),
                                             Elipse::Checkered, false);
                connect(goal, SIGNAL(dying(Elipse*)), level, SLOT(itemDying(Elipse*)));
                emit newElipseItem(goal);
            } else if (splitvec.front() == "name") {
                std::string temp = splitvec[1];
                boost::algorithm::trim(temp);
                level->levelName = temp.c_str();
                emit changeLevelName(level->levelName);
            } else {
                // If execution reaches this point, may the gods have mercy on your soul
            }
        }
        input.close();
    }
    else {
        std::cerr << "Could not read from file: \"" << level->filename.toStdString() << "\"" << std::endl;
    }
    return;
}

void Editor::deleteSelected() {
    QList<QGraphicsItem *> selected = level->scene()->selectedItems();
    if (!selected.isEmpty()) {
        QGraphicsItem * itemToDelete = selected[0];
        level->scene()->removeItem(itemToDelete);
        delete itemToDelete;
    }
}
