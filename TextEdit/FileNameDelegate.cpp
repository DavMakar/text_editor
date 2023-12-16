#include "FileNameDelegate.hpp"
#include <QLineEdit>

FilenameDelegate::FilenameDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{
}

QWidget *FilenameDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void FilenameDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if(lineEdit){

        lineEdit->setText(index.data(Qt::DisplayRole).toString());
    }
}

void FilenameDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if (lineEdit)
    {
        model->setData(index, lineEdit->text(), Qt::DisplayRole);
    }
}

