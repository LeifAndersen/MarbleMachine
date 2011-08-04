#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
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
    void changeItemName(QString);
    void changeItemX(QString);
    void changeItemY(QString);
    void changeItemRadius(QString);
    void changeLevelName(QString);
    void changeX0(QString);
    void changeX1(QString);
    void changeY0(QString);
    void changeY1(QString);

private:
    Ui::MainWindow *ui;

    std::vector<LevelObject *> objects;
};

#endif // MAINWINDOW_H
