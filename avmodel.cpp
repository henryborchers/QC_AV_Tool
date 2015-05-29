#include "avmodel.h"
#include "MediaInfoDLL.h"
#include <QtDebug>
#include <QFileInfo>
#include "VideoObject.h"
#include "AudioObject.h"

AVModel::AVModel(QObject *parent):QAbstractTableModel(parent)
{
//    QVariant rower[3];
//    rower[0]= 34;
//    rower[1] = "4554";
//    RowData row1;
////    row1.fileName = NULL;
////    row1.fileSize = NULL;
//    row1.fileType = "gggggg";
//    this->m_files.append(row1);


//    QVariant value(34);
//    QVariantList *temp= new QVariantList();
//    temp->append(value);
//    this->m_files.append(temp);
}

AVModel::~AVModel()
{

}

int AVModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "rowCount: " << m_files.size();
    return this->m_files.size();
}


int AVModel::columnCount(const QModelIndex &parent) const
{

    return this->column_size;
}
bool AVModel::setData(const QModelIndex &index, const QVariant &value, int role){
//    if(role == Qt::EditRole)
//    {
//        this->m_data[index.row()][index.column()] = value.toString();
//        qDebug() << "sadfsadf";
//    }
    return true;

}

QVariant AVModel::data(const QModelIndex &index, int role) const
{
    int col_index = index.column();
    int row_index = index.row();
    switch(role){
    case Qt::DisplayRole:
        switch(col_index) {
        case AVModel::fileName:
            return m_files[row_index]->getFileName().c_str();
            break;
        case AVModel::fileSize:
            return "-";
//            return m_files[row_index]->getFileSize();
//            return m_files[row_index].fileSize;
//            return m_data[row_index][AVModel::fileSize];
            case AVModel::fileType:
            return "-";
//            return m_files[row_index].fileType;
//            return m_data[row_index][AVModel::fileType];
        case AVModel::duration:
            return m_files[row_index]->getDurationString().c_str();
//            QString foo = m_data[0][1];
                break;
        }



//        return row[col_index];
    }
    return QVariant();
}

QVariant AVModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if(role == Qt::DisplayRole) {

        if (orientation == Qt::Horizontal){
            switch(section){
            case AVModel::fileName:
                return QString("File Name");
            case AVModel::fileSize:
                return QString("File Size");
            case AVModel::fileType:
                return QString("Files type");
            case AVModel::duration:
                return QString("Duration");
            }

        }

    }
    return QVariant();
}

bool AVModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);
//    qDebug() << position;
//    QVariant data;
//    data << row;

    endInsertRows();
    return true;
}

bool AVModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    qDebug() << position;
    beginRemoveRows(QModelIndex(), position, position+rows-1);
//    for(auto it = this->m_files.begin(); it != this->m_files.end(); ++it){
//    if( (*it)->)
//    }
//    auto d = this->m_files.at(position);
    if(position < this->m_files.size()){
        delete this->m_files[position];
        this->m_files.erase(m_files.begin() + position);
    }

    endRemoveRows();

    return true;

}

bool AVModel::addFile(const QString &fileName)
{
//    RowData newRow;
    QFileInfo checkFile(fileName);
    if (checkFile.exists()) {

        VideoObject *newRow = new VideoObject(fileName.toStdString());
        this->m_files.append(newRow);
    } else {


    }
//    this->m_files.append(newRow);
    this->insertRows(this->rowCount(),1);

//bool AVModel::addFile(const QString &fileName)
//{
//    using namespace MediaInfoDLL;
//    RowData newRow;
//    QFileInfo checkFile(fileName);
//    if (checkFile.exists()) {
//        MediaInfo Mi;
//        Mi.Open(fileName.toStdString());
//        if(Mi.IsReady()){
//            qDebug() << fileName;
//            newRow.fileName = fileName;
//            newRow.fileSize = (unsigned int) std::stoi(Mi.Get(Stream_General, 0, __T("FileSize"), Info_Text, Info_Name));
//            newRow.fileType = Mi.Get(Stream_General, 0, __T("Format"), MediaInfoDLL::Info_Text, MediaInfoDLL::Info_Name).c_str();
//        }
//
//        Mi.Close();
//    } else {
//        newRow.fileName = "UNDEFINED";
//        newRow.fileSize = 0;
//        newRow.fileType = "None";
//
//    }
//    this->m_files.append(newRow);
//    this->insertRows(this->rowCount(),1);
}
bool AVModel::removeFile(int row)
{
//    if(m_files.size() > 0){
//        this->m_files.pop_back();
        this->removeRows(this->rowCount()-1, 1);
    return true;
//    }
}

