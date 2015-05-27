#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDirIterator>
#include <QtDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList headers;

    model = new AVModel(this);
    ui->FilesView->setModel(model);
    loadTestFiles();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionOpen_Folder_triggered()
{
    qDebug() << "Opening folder";
}

void MainWindow::on_actionAdd_Row_triggered()
{
    qDebug() << "adding row";
    model->addFile("asfddsaf");

}

void MainWindow::on_actionTest_triggered()
{
//    model->addRow("asdfasdfsdaf");


}

void MainWindow::on_actionRemove_Row_triggered()
{
    qDebug() << "Row removed. model->rowCount(): " << model->rowCount();
    if(model->rowCount() > 0) {
        model->removeFile(model->rowCount());
    }
}

void MainWindow::loadTestFiles()
{
    qDebug() << "Loading all files";
    QDir testFolder("D:/media/tv/TimeTrax");
    if(not testFolder.exists()){
        qDebug() << "Can't find test folder";
    } else {
        qDebug() << "Found the test folder" << testFolder.absolutePath();
        QStringList AVI_Files;
        QDirIterator it(testFolder.absolutePath(), QStringList() << "*.avi", QDir::Files);
        while (it.hasNext()) {
            this->model->addFile(it.next());
        }
    }

}
