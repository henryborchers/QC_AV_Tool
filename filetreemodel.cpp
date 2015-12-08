#include <QtGui>
#include "treeitem.h"
#include "filetreemodel.h"

fileTreeModel::fileTreeModel(const QObject *parent)
{
    QVector<QVariant> headers;
    headers << "File Name" << "File Size";
    rootItem = new TreeItem(headers);
}

fileTreeModel::fileTreeModel(const QStringList &headers, QObject *parent)
{
    QVector<QVariant> rootData;
    foreach(QString header, headers)
        rootData << header;
    rootItem = new TreeItem(rootData);
}

fileTreeModel::fileTreeModel(const QStringList &headers, const QString &data, QObject *parent) : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    foreach(QString header, headers)
        rootData << header;

    rootItem = new TreeItem(rootData);
    setupModelData(data.split(QString("\n")), rootItem);
}

fileTreeModel::~fileTreeModel()
{
    delete rootItem;
}

int fileTreeModel::columnCount(const QModelIndex &parent) const
{
    return rootItem->columnCount();
}

QVariant fileTreeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem *item = getItem(index);

    return item->data(index.column());
}

Qt::ItemFlags fileTreeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

TreeItem *fileTreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if(item) return item;
    }
    return rootItem;
}

QVariant fileTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex fileTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.isValid() && parent.column() != 0)
        return QModelIndex();

    TreeItem *parentItem = getItem(parent);

    TreeItem *childItem = parentItem->child((row));
    if(childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

bool fileTreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool fileTreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

QModelIndex fileTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parent();

    if(parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool fileTreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if(rootItem->columnCount() == 0)
        removeRows(0, rowCount());
    return success;
}

bool fileTreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

int fileTreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem = getItem(parent);

    return parentItem->childCount();
}

bool fileTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if(result)
        emit dataChanged(index, index);

    return result;
}

bool fileTreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool results = rootItem->setData(section, value);

    if(results)
        emit headerDataChanged(orientation, section, section);

    return results;
}

QList<QStandardItem*> fileTreeModel::addRow(const QString &fileName, const QModelIndex &parent)
{
    QList<TreeItem*> parents;
//    parents << parent;
    QVector<QVariant> rowOfFiles;
    rowOfFiles << fileName;
//    qDebug() << parents.last();

}


void fileTreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
{
    QList<TreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while(number < lines.count()) {
        int position = 0;
        while(position < lines[number].length()){
            if (lines[number].mid(position, 1) != " ")
                break;
            position++;
        }

        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QVector<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if(position >indentations.last()){
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if(parents.last()->childCount() > 0){
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0){
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            TreeItem *parent = parents.last();
            parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < columnData.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);

        }

        number++;
    }
}
