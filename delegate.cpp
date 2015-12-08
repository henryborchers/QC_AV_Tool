#include "delegate.h"
#include "avmodel.h"
#include <QDebug>
#include <QComboBox>
Delegate::Delegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QComboBox *editor = new QComboBox(parent);
    switch(index.column()){
        case AVModel::CLM_QC_PRIORITY:
            editor->addItem("Low");
            editor->addItem("Normal");
            editor->addItem("High");
            break;

        case AVModel::CLM_QUALITY_VALUE:
            editor->addItem("Unknown");
            editor->addItem("Passed");
            editor->addItem("Failed");
            break;
    }
    return editor;
}

void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const {

    int value = index.model()->data(index, Qt::EditRole).toInt();
    QComboBox *options = static_cast<QComboBox*>(editor);
    options->setCurrentIndex(value);


}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {

    QComboBox *options = static_cast<QComboBox*>(editor);
    int value = options->currentIndex();
    model->setData(index, value, Qt::EditRole);
}
