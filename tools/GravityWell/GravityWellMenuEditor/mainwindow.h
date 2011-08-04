#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

#include "LevelObject.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void exitApp();
    void addItem();
    void deleteItem();
    void moveItemUp();
    void moveItemDown();

private:
    Ui::MainWindow *ui;

    std::vector<LevelObject *> objects;
};

#endif // MAINWINDOW_H
