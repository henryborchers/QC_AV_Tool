#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDirIterator>
#include <QtDebug>

#include "MediaPlayer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new AVModel(this);
    testModel = new QStandardItemModel(2,2, this);
    myDelegate = new Delegate(this);

    mapper = new QDataWidgetMapper;
    mapper->setModel(model);
    mapper->addMapping(ui->le_fileName, AVModel::CLM_FILE_NAME);
    mapper->addMapping(ui->le_type, AVModel::CLM_MEDIA_TYPE);
    mapper->addMapping(ui->le_duration, AVModel::CLM_DURATION);
    mapper->addMapping(ui->le_audioCodec, AVModel::CLM_AUDIO_CODEC);
    mapper->addMapping(ui->cb_priority, AVModel::CLM_QC_PRIORITY, "currentIndex");
    mapper->addMapping(ui->cb_quality, AVModel::CLM_QUALITY_VALUE, "currentIndex");
    mapper->addMapping(ui->cb_progress, AVModel::CLM_PROGRESS_STATUS);

    ui->FilesView->setModel(model);
    ui->FilesView->setColumnHidden(AVModel::CLM_FILE_SIZE, true);
    ui->FilesView->setColumnHidden(AVModel::CLM_CONTAINER_TYPE, true);
    ui->FilesView->setItemDelegate(myDelegate);
    ui->FilesView->setAlternatingRowColors(true);

    loadTestFiles();
//    ui->FilesView->openPersistentEditor(model->index(7, 1));


    mapper->toFirst();
    qDebug() << mapper->currentIndex();
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
    mapper->toNext();
    qDebug() << mapper->currentIndex();
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
//        int i = 0;
        while (it.hasNext()) {
            this->model->addFile(it.next());
//            ui->FilesView->openPersistentEditor(model->index(i, 7));
//            ui->FilesView->openPersistentEditor(model->index(i, 9));
//            ++i;
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
    model->setActiveRow(index.row());
    mapper->setCurrentIndex(index.row());
//    ui->FilesView->ui;

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

void MainWindow::on_btn_play_clicked()
{
    // TODO: Replace playbutton click with a selection file name
    std::string playFile = ui->le_fileName->text().toStdString();
    qDebug() << "Playing:" << playFile.c_str();
    MediaPlayer player(playFile);

}
