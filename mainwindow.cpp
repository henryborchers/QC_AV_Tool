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
    model = new AVModel(this);
    myDelegate = new Delegate(this);
    ui->FilesView->setModel(model);
    ui->FilesView->setItemDelegate(myDelegate);
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
    qDebug() << "Action";
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
    QDir testFolder("D:/media/tv/Looney tunes/Vol 3/Disc1");
    if(not testFolder.exists()){
        qDebug() << "Can't find test folder";
    } else {
        qDebug() << "Found the test folder" << testFolder.absolutePath();
        QDirIterator it(testFolder.absolutePath(), QStringList() << "*.mp4", QDir::Files);
        while (it.hasNext()) {
            this->model->addFile(it.next());
        }
    }

}

void MainWindow::on_actionAbout_triggered()
{
    qDebug() << "Loading about menu";
}

void MainWindow::on_FilesView_activated(const QModelIndex &index)
{
    qDebug() << "on_FilesView_activated";
//    qDebug() << index.data(Qt::DisplayRole);

}

void MainWindow::loadRecord(int index) {
    qDebug() << "index" << index;
//    this->mapper->
}
void MainWindow::on_actionSet_All_Items_as_Done_triggered()
{
    qDebug() << "Setting all items as done";
}
