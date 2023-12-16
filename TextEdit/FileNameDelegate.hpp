#ifndef FILENAME_DELEGATE_HPP
#define FILENAME_DELEGATE_HPP

#include <QStyledItemDelegate>

class FilenameDelegate : public QStyledItemDelegate
{
//    Q_OBJECT
public:
    FilenameDelegate(QObject* parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option , const QModelIndex &index);
    void setEditorData(QWidget *editor , const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
//signals:
//    void setOldFilename(const QString& filename) const;
//    void updateFilename(const QString& filename) const;
};

#endif // FILENAME_DELEGATE_HPP
