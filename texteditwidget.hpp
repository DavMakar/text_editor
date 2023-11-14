#ifndef TEXTEDITWIDGET_HPP
#define TEXTEDITWIDGET_HPP

#include <QWidget>
#include <QTextEdit>
#include <QString>
#include <QSqlDatabase>
#include <QSqlTableModel>

class TextEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextEditWidget(int id , QSqlDatabase& db, QWidget *parent = nullptr);
    void setText(const QString&);
    void setId(int id);
private:
    QString getColumnName(int col);
signals:
    void saveSignal(QString);
private slots:
    void saveButtonClicked();

private:
    int userId_;
    QTextEdit* textEdit_;
    QSqlDatabase& db_;
    QSqlTableModel* model_;
};

#endif // TEXTEDITWIDGET_HPP
