#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

// Used to generate a unique identifier
unsigned long makeId() {
    static unsigned long nextId = 0;
    return ++nextId;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    activeLevelObject(NULL)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{

}

void MainWindow::openFile()
{

}

void MainWindow::saveFile()
{

}

void MainWindow::saveAsFile()
{

}

void MainWindow::exitApp()
{
    QCoreApplication::quit();
}

void MainWindow::addItem()
{

}

void MainWindow::deleteItem()
{

}

void MainWindow::moveItemUp()
{

}

void MainWindow::moveItemDown()
{

}

void MainWindow::changeItemName(QString name)
{
    if(activeLevelObject == NULL)
        return;
}

void MainWindow::changeItemX(QString x)
{
    if(activeLevelObject == NULL)
        return;
    bool worked;
    x.toFloat(&worked);
    if(worked)
        activeLevelObject->xPos = x.toFloat();
}

void MainWindow::changeItemY(QString y)
{
    if(activeLevelObject == NULL)
        return;
    bool worked;
    y.toFloat(&worked);
    if(worked)
        activeLevelObject->yPos = y.toFloat();
}

void MainWindow::changeItemRadius(QString rad)
{
    if(activeLevelObject == NULL)
        return;
    bool worked;
    rad.toFloat(&worked);
    if(worked)
        /* */;
}

void MainWindow::changeLevelName(QString name)
{
    this->name = name;
}

void MainWindow::changeX0(QString x0)
{
    this->x0 = x0.toFloat();
}

void MainWindow::changeX1(QString x1)
{
    this->x1 = x1.toFloat();
}

void MainWindow::changeY0(QString y0)
{
    this->y0 = y0.toFloat();
}

void MainWindow::changeY1(QString y1)
{
    this->y1 = y1.toFloat();
}
