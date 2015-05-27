#include "avmodel.h"
#include "MediaInfoDLL.h"
#include <QtDebug>
#include <QFileInfo>

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
            if(m_files[row_index].fileName != NULL)
                return m_files[row_index].fileName;
            else return QVariant();
            break;
        case AVModel::fileSize:
            return m_files[row_index].fileSize;
//            return m_data[row_index][AVModel::fileSize];
        case AVModel::fileType:
            return m_files[row_index].fileType;
//            return m_data[row_index][AVModel::fileType];
        case AVModel::foo:
            QString foo = m_data[0][1];
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
            case AVModel::foo:
                return QString("Foo");
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

    beginRemoveRows(QModelIndex(), position, position+rows-1);
    endRemoveRows();

    return true;

}

bool AVModel::addFile(const QString &fileName)
{
    using namespace MediaInfoDLL;
    RowData newRow;
    QFileInfo checkFile(fileName);
    if (checkFile.exists()) {
        MediaInfo Mi;
        Mi.Open(fileName.toStdString());
        if(Mi.IsReady()){
            qDebug() << fileName;
            newRow.fileName = fileName;
            newRow.fileSize = (unsigned int) std::stoi(Mi.Get(Stream_General, 0, __T("FileSize"), Info_Text, Info_Name));
            newRow.fileType = Mi.Get(Stream_General, 0, __T("Format"), MediaInfoDLL::Info_Text, MediaInfoDLL::Info_Name).c_str();
        }

        Mi.Close();
    } else {
        newRow.fileName = "UNDEFINED";
        newRow.fileSize = 0;
        newRow.fileType = "None";

    }
    this->m_files.append(newRow);
    this->insertRows(this->rowCount(),1);
}
bool AVModel::removeFile(int row)
{
    if(m_files.size() > 0){
        this->m_files.pop_back();
        this->removeRows(this->rowCount(), 1);
    }
}

