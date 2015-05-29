#ifndef AVMODEL_H
#define AVMODEL_H
#include <QAbstractTableModel>
#include <QString>
#include "AV_Item.h"
const int ROWS    = 1;
const int COLUMNS = 4;
struct RowData {
    QString fileName;
    int fileSize;
    QString fileType;
};

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
    bool addFile(const QString & fileName);
    bool removeFile(int row);
private:

    int row_size = 1;
    int column_size = 4;
    enum columnNames {fileName = 0,
                      fileSize = 1,
                      fileType = 2,
                      duration = 3};
//    QVector<QVariantList*> m_files;
//    QVector<RowData> m_files;
    QVector<AV_Item*> m_files;
    QVariantList newRow;
    QString m_data[ROWS][COLUMNS];
};

#endif // AVMODEL_H
