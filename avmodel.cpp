#include "avmodel.h"
#include <QtDebug>
#include <QFileInfo>
#include "VideoObject.h"
#include "AudioObject.h"



AVModel::AVModel(QObject *parent):QAbstractTableModel(parent)
{

}

AVModel::~AVModel()
{

}

int AVModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
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

    int col_index = index.column();
    int row_index = index.row();
    if(role==Qt::EditRole) {
        switch(col_index) {
            case AVModel::QC_PRIORITY:
                m_files[row_index]->setPriority((AV_Item::QCPriority)value.toInt());
                break;
            case AVModel::QUALITY_VALUE:

                m_files[row_index]->setQuality((AV_Item::QualityValue)value.toInt());
                break;

            default:
                break;
        }
    }
    return true;

}

QVariant AVModel::data(const QModelIndex &index, int role) const
{
    int col_index = index.column();
    int row_index = index.row();
    switch(role){
        case Qt::DisplayRole:
            switch(col_index) {
                case AVModel::FILE_NAME:
                    return m_files[row_index]->getFileName().c_str();

                case AVModel::FILE_SIZE:
                    return "-";
                    case AVModel::MEDIA_TYPE:
                        return m_files[row_index]->getMediaTypeString();
                    case AVModel::CONTAINER_TYPE:
                        return "-";
                case AVModel::DURATION:
                    return m_files[row_index]->getDurationString().c_str();
                case AVModel::AUDIO_CODEC:
                    return m_files[row_index]->getAudioCodec().c_str();
                case AVModel::VIDEO_CODEC:
                    if(m_files[row_index]->getMediaType()==AV_Item::MediaType::VIDEO){
                        return m_files[row_index]->getVideoCodec().c_str();
                    } else {
                        return "-";
                    }
                case AVModel::QC_PRIORITY:
                    switch(m_files[row_index]->getPriority()) {
                        case AV_Item::LOW_PRIORITY:
                            return "Low";

                        case AV_Item::NORMAL_PRIORITY:
                            return "Normal";

                        case AV_Item::HIGH_PRIORITY:
                            return "High";
                        default:
                            return "INVALID OPTION";
                    }

                case AVModel::QUALITY_VALUE:
                    switch(m_files[row_index]->getQuality()) {
                        case AV_Item::UNKNOWN_QUALITY:
                            return "Unknown";
                        case AV_Item::PASS:
                            return "Passed";
                        case AV_Item::FAIL:
                            return "Failed";
                        default:
                            return "INVALID OPTION";

                    }
                case AVModel::PROGRESS_STATUS:
                    switch(m_files[row_index]->getProgress()){
                        case AV_Item::TO_BE_CHECKED:
                            return "To Be Checked";
                        case AV_Item::CHECKING:
                            return "Checking";
                        case AV_Item::COMPLETED:
                            return "Completed";
                        case AV_Item::DEFERRED:
                            return "Deferred";
                        default:
                            return "INVALID OPTION";
                    }

                default: break;

            }

        default: break;

//        return row[col_index];
    }
    return QVariant();
}

QVariant AVModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if(role == Qt::DisplayRole) {

        if (orientation == Qt::Horizontal){
            switch(section){
                case AVModel::FILE_NAME:
                    return QString("File Name");
                case AVModel::FILE_SIZE:
                    return QString("File Size");
                case AVModel::MEDIA_TYPE:
                    return QString("Media Type");
                case AVModel::DURATION:
                    return QString("Duration");
                case AVModel::AUDIO_CODEC:
                    return QString("Audio Codec");
                case AVModel::VIDEO_CODEC:
                    return QString("Video Codec");
                case AVModel::CONTAINER_TYPE:
                    return QString("Container Type");
                case AVModel::QC_PRIORITY:
                    return QString("Priority");
                case AVModel::PROGRESS_STATUS:
                    return QString("Progress");
                case AVModel::QUALITY_VALUE:
                    return QString("Quality");
                default:
                    return QVariant();
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
        this->insertRows(this->rowCount(),1);
        return true;
    }
    return false;
}

bool AVModel::removeFile(int row)
{
//    if(m_files.size() > 0){
//        this->m_files.pop_back();
        this->removeRows(this->rowCount()-1, 1);
    return true;
}

Qt::ItemFlags AVModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return 0;
    switch(index.column()){
        case AVModel::QC_PRIORITY:
            return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
        case AVModel::QUALITY_VALUE:
            return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
        default:
            return QAbstractItemModel::flags(index);
    }
}

