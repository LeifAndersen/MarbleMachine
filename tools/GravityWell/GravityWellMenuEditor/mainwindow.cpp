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
