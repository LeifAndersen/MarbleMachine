#include "Mapper.h"

Mapper::Mapper(QWidget *parent)
    : QWidget(parent)
{
    idBase = 0;

    QGridLayout * gridLayout = new QGridLayout;

    gridLayout->setSpacing(5);

    texturefield = new TextureField(this);
    texturefield->setMaximumHeight(900);
    texturefield->setMaximumWidth(900);
    connect(this, SIGNAL(newTexture(QPixmap *)), texturefield, SLOT(newTexture(QPixmap *)));
    gridLayout->addWidget(texturefield, 0, 2, 12, 1);


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

    QPushButton * removeCursorButton = new QPushButton("Remove\nLast Cursor");
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
    connect(this, SIGNAL(newXText(QString)), xPosEdit, SLOT(setText(QString)));
    gridLayout->addWidget(xPosEdit, 3, 1, Qt::AlignCenter);

    QLabel * xPosLabel = new QLabel("X Position");
    gridLayout->addWidget(xPosLabel, 3, 0, Qt::AlignCenter);

    //

    QLineEdit * yPosEdit = new QLineEdit();
    yPosEdit->setValidator(iValid);
    yPosEdit->setMaximumWidth(100);
    connect(yPosEdit, SIGNAL(textEdited(QString)), this, SLOT(setYPos(QString)));
    connect(this, SIGNAL(newYText(QString)), yPosEdit, SLOT(setText(QString)));
    gridLayout->addWidget(yPosEdit, 4, 1, Qt::AlignCenter);

    QLabel * yPosLabel = new QLabel("Y Position");
    gridLayout->addWidget(yPosLabel, 4, 0, Qt::AlignCenter);

    //

    cursorSelect = new QComboBox();
    connect(cursorSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(cursorChanged(int)));
    gridLayout->addWidget(cursorSelect, 2, 1, Qt::AlignCenter);

    QLabel * cursorSelectLabel = new QLabel("Current Cursor");
    gridLayout->addWidget(cursorSelectLabel, 2, 0, Qt::AlignCenter);

    //

    QLineEdit * buttonNameEdit = new QLineEdit();
    buttonNameEdit->setMaximumWidth(100);
    connect(buttonNameEdit, SIGNAL(textEdited(QString)), this, SLOT(setButtonName(QString)));
    gridLayout->addWidget(buttonNameEdit, 5, 1, Qt::AlignCenter);

    QLabel * buttonNameLabel = new QLabel("Button Name");
    gridLayout->addWidget(buttonNameLabel, 5, 0, Qt::AlignCenter);

    setLayout(gridLayout);
}

Mapper::~Mapper()
{

}

void Mapper::openTexture() {
    QString fname = QFileDialog::getOpenFileName(this, tr("Open Texture"),
                                                        "",
                                                        tr("Images (*.bmp *.gif *.jpg *.jpeg *.png)"));
    if (!fname.isNull()) {
        // File Opened Successfully
        // clear all the cursors
        while (!cursors.empty()) {
            removeCursor();
        }
        // load the new texture
        QPixmap * texture = new QPixmap(fname);
        emit newTexture(texture);
    }
}

void Mapper::saveCoordinates() {
    // TODO -- understand the format and get to a point where there is data to be saved.
    std::cerr << buttonName.toStdString() << ":";

    for (std::vector<Cursor *>::iterator i = cursors.begin(); i != cursors.end(); i++) {
        std::cerr << (*i)->x() << "," << (*i)->y() << ";";
    }
    std::cerr << std::endl;
}

void Mapper::addCursor() {
    Cursor * cursor = new Cursor(idBase++,
                                 texturefield->scene()->width(),
                                 texturefield->scene()->height());
    // add to scene
    texturefield->scene()->addItem(cursor);
    // set position
    cursor->setPos(texturefield->mapToScene(222, 222));
    // add to list
    cursors.push_back(cursor);
    // add to combo box
    cursorSelect->insertItem(cursor->id, boost::lexical_cast<std::string>(cursor->id + 1).c_str());
    // connect x and y change signal/slot pairs
    connect(cursor, SIGNAL(newX(int)), this, SLOT(setXPos(int)));
    connect(cursor, SIGNAL(newY(int)), this, SLOT(setYPos(int)));
    // get selection changes
    connect(cursor, SIGNAL(cursorSelected(uint)), this, SLOT(cursorSelected(uint)));
    // receive notice when it dies
    connect(cursor, SIGNAL(dying(Cursor*)), this, SLOT(cursorDying(Cursor*)));
    // select new cursor and clear all other selection
    texturefield->scene()->clearSelection();
    cursor->setSelected(true);
}

void Mapper::removeCursor() {
    // check if there are any cursors to delete
    if (cursors.empty()) {
        return;
    }
    // Clear the selection so that nothing else gets deleted by mistake
    texturefield->scene()->clearSelection();
    // tell the item to delete that it is selected
    cursors.back()->setSelected(true);
    // get the qgraphicsitem pointer to the item from the scene via selection
    QList<QGraphicsItem *> selected = texturefield->scene()->selectedItems();
    QGraphicsItem * itemToDelete = selected[0];
    // remove the item from the scene
    texturefield->scene()->removeItem(itemToDelete);
    // delete the item (calls this->cursorDying(Cursor *)) by popping it from the list
    cursors.pop_back();
    delete itemToDelete;
}

void Mapper::setXPos(QString xPos) {
    cursors[cursorSelect->currentIndex()]->setX(xPos.toDouble());
}

void Mapper::setXPos(int xPos) {
    emit newXText(QString(boost::lexical_cast<std::string>(xPos).c_str()));
}

void Mapper::setYPos(QString yPos) {
    cursors[cursorSelect->currentIndex()]->setY(yPos.toDouble());
}

void Mapper::setYPos(int yPos) {
    emit newYText(QString(boost::lexical_cast<std::string>(yPos).c_str()));
}

void Mapper::cursorChanged(int selection) {
    // TODO -- need to change color of selected cursor
}

void Mapper::cursorDying(Cursor * dying) {
    // get the id of the dying
    unsigned int id = dying->id;
    // delete it from the combobox
    cursorSelect->removeItem(id);
    // ???
    idBase--;
    // profit
    if (idBase == 0) {
        // clear position edit
        emit newXText(QString(""));
        emit newYText(QString(""));
    } else {
        cursorSelect->setCurrentIndex(idBase - 1);
        cursors[idBase - 1]->setSelected(true);
    }
}

void Mapper::cursorSelected(unsigned int id) {
    cursorSelect->setCurrentIndex(id);
    setXPos(cursors[id]->x());
    setYPos(cursors[id]->y());
}

void Mapper::setButtonName(QString _name) {
    buttonName = _name;
}
