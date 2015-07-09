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
//    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    void setActiveRow(int row);
    int getActiveRow();

    bool addFile(const QString & fileName);
    bool removeFile(int row);

    enum columnNames {
        CLM_FILE_NAME = 0,
        CLM_FILE_SIZE = 1,
        CLM_MEDIA_TYPE = 2,
        CLM_CONTAINER_TYPE = 3,
        CLM_DURATION = 4,
        CLM_AUDIO_CODEC = 5,
        CLM_VIDEO_CODEC = 6,
        CLM_QC_PRIORITY = 7,
        CLM_PROGRESS_STATUS = 8,
        CLM_QUALITY_VALUE = 9};

private:
    int column_size = 10;
    int activeRow;
//    QVector<QVariantList*> m_files;
//    QVector<RowData> m_files;
    QVector<AV_Item*> m_files;
//    QVariantList newRow;
//    QString m_data[ROWS][COLUMNS];
};

#endif // AVMODEL_H
