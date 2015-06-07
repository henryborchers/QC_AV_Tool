#ifndef AVMODEL_H
#define AVMODEL_H
#include <QAbstractTableModel>
#include <QString>
#include "AV_Item.h"

class AVModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    AVModel(QObject *parent);
    ~AVModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    bool addFile(const QString & fileName);
    bool removeFile(int row);


    enum columnNames {
        FILE_NAME = 0,
        FILE_SIZE = 1,
        MEDIA_TYPE = 2,
        CONTAINER_TYPE = 3,
        DURATION = 4,
        AUDIO_CODEC = 5,
        VIDEO_CODEC = 6,
        QC_PRIORITY = 7,
        PROGRESS_STATUS = 8,
        QUALITY_VALUE = 9};

private:
    int column_size = 10;
//    QVector<QVariantList*> m_files;
//    QVector<RowData> m_files;
    QVector<AV_Item*> m_files;
//    QVariantList newRow;
//    QString m_data[ROWS][COLUMNS];
};

#endif // AVMODEL_H
