#include "avmodel.h"
#include <QtDebug>
#include <QFileInfo>
#include <QFont>
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
        if(value.toInt() != 0)
        {

            switch(col_index) {
                case AVModel::CLM_QC_PRIORITY:

                    m_files[row_index]->setPriority((AV_Item::QCPriority)value.toInt());
                    break;
                case AVModel::CLM_QUALITY_VALUE:

                    m_files[row_index]->setQuality((AV_Item::QualityValue)value.toInt());
                    break;

                default:
                    break;

            }
            QVector<int> roles;
            roles.append(Qt::DisplayRole);
            emit dataChanged(index, index, roles);
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
                case AVModel::CLM_FILE_NAME:
                    return m_files[row_index]->getFileName().c_str();

                case AVModel::CML_FILE_SIZE:
                    return "-";
                    case AVModel::CLM_MEDIA_TYPE:
                        return m_files[row_index]->getMediaTypeString();
                    case AVModel::CLM_CONTAINER_TYPE:
                        return "-";
                case AVModel::CLM_DURATION:
                    return m_files[row_index]->getDurationString().c_str();
                case AVModel::CLM_AUDIO_CODEC:
                    return m_files[row_index]->getAudioCodec().c_str();
                case AVModel::CLM_VIDEO_CODEC:
                    if(m_files[row_index]->getMediaType()==AV_Item::MediaType::MT_VIDEO){
                        return m_files[row_index]->getVideoCodec().c_str();
                    } else {
                        return "-";
                    }
                case AVModel::CLM_QC_PRIORITY:
                    switch(m_files[row_index]->getPriority()) {
                        case AV_Item::PRIORITY_LOW:
                            return "Low";

                        case AV_Item::PRIORITY_NORMAL:
                            return "Normal";

                        case AV_Item::PRIORITY_HIGH:
                            return "High";
                        default:
                            return "INVALID OPTION";
                    }

                case AVModel::CLM_QUALITY_VALUE:
                    switch(m_files[row_index]->getQuality()) {
                        case AV_Item::QV_UNKNOWN:
                            return "Unknown";
                        case AV_Item::QV_PASS:
                            return "Passed";
                        case AV_Item::QV_FAIL:
                            return "Failed";
                        default:
                            return "INVALID OPTION";

                    }
                case AVModel::CLM_PROGRESS_STATUS:
                    switch(m_files[row_index]->getProgress()){
                        case AV_Item::PS_UNCHECKED:
                            return "To Be Checked";
                        case AV_Item::PS_CHECKING:
                            return "Checking";
                        case AV_Item::PS_COMPLETED:
                            return "Completed";
                        case AV_Item::PS_DEFERRED:
                            return "Deferred";
                        default:
                            return "INVALID OPTION";
                    }

                default: break;

            }
        case Qt::EditRole:
            switch(col_index){
                case AVModel::CLM_QC_PRIORITY:
                    return m_files[row_index]->getPriority();
                case AVModel::CLM_QUALITY_VALUE:
                    return m_files[row_index]->getQuality();

            }
        case Qt::FontRole:
            if(row_index == activeRow) {
                QFont boldFont;
                boldFont.setBold(true);
                return boldFont;
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
                case AVModel::CLM_FILE_NAME:
                    return QString("File Name");
                case AVModel::CML_FILE_SIZE:
                    return QString("File Size");
                case AVModel::CLM_MEDIA_TYPE:
                    return QString("Media Type");
                case AVModel::CLM_DURATION:
                    return QString("Duration");
                case AVModel::CLM_AUDIO_CODEC:
                    return QString("Audio Codec");
                case AVModel::CLM_VIDEO_CODEC:
                    return QString("Video Codec");
                case AVModel::CLM_CONTAINER_TYPE:
                    return QString("Container Type");
                case AVModel::CLM_QC_PRIORITY:
                    return QString("Priority");
                case AVModel::CLM_PROGRESS_STATUS:
                    return QString("Progress");
                case AVModel::CLM_QUALITY_VALUE:
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
        case AVModel::CLM_QC_PRIORITY:
            return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
        case AVModel::CLM_QUALITY_VALUE:
            return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
        default:
            return QAbstractItemModel::flags(index);
    }
}

void AVModel::setActiveRow(int row) {
    qDebug() << "Changing active row to " << row;
    activeRow = row;

    QModelIndex topLeft = index(0,0);
    QModelIndex bottomRight = index(rowCount() - 1,columnCount() - 1);
    QVector<int> roles;
    roles.append(Qt::FontRole);
    emit dataChanged(topLeft, bottomRight, roles);
}

int AVModel::getActiveRow() {
    return activeRow;
}
