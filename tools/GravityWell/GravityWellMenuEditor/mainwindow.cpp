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
    ui(new Ui::MainWindow)
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

}

void MainWindow::changeItemX(QString x)
{

}

void MainWindow::changeItemY(QString y)
{

}

void MainWindow::changeItemRadius(QString rad)
{

}

void MainWindow::changeLevelName(QString name)
{

}

void MainWindow::changeX0(QString x0)
{

}

void MainWindow::changeX1(QString x1)
{

}

void MainWindow::changeY0(QString y0)
{

}

void MainWindow::changeY1(QString y1)
{

}
