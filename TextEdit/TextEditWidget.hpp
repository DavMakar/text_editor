#ifndef TEXT_EDIT_WIDGET_HPP
#define TEXT_EDIT_WIDGET_HPP

#include <QWidget>
#include <QTextEdit>
#include <QString>
#include <QSqlDatabase>
#include <QModelIndex>

class UserDataManager;
class QItemSelection;
class QStringListModel;
class QItemSelectionModel;

class TextEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextEditWidget(int id , UserDataManager& dbFacade, QWidget *parent = nullptr);
    void setText(const QString&);
    void setId(int id);

private:
    QString filenameFromIndex(const QModelIndex& index);

signals:
    void saveSignal(QString);
private slots:
    void setOldFilenameSlot(const QModelIndex& index);
    void updateFilenameSlot(QWidget* editor);
    void createNewFileSlot();
    void saveFileSlot();
    void deleteSlot();
    void undoSlot();
    void redoSlot();

    void selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);

private:
    int userId_;
    UserDataManager& db;
    QString oldFilename;
    QTextEdit* textEdit_;
    QStringListModel* slModel_;
    QItemSelectionModel* selectionModel;
};

#endif // TEXT_EDIT_WIDGET_HPP
