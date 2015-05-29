#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "filetreemodel.h"
#include "avmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionOpen_Folder_triggered();

    void on_actionAdd_Row_triggered();

    void on_actionTest_triggered();

    void on_actionRemove_Row_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    void loadTestFiles();

//    fileTreeModel *model;
    AVModel *model;
};

#endif // MAINWINDOW_H
