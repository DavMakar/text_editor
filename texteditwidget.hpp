#ifndef TEXTEDITWIDGET_HPP
#define TEXTEDITWIDGET_HPP

#include <QWidget>
#include <QTextEdit>
#include <QString>

class TextEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextEditWidget(QWidget *parent = nullptr);
    void setText(const QString&);

signals:
    void saveSignal(QString);
private slots:
    void saveButtonClicked();

private:
    QTextEdit* textEdit_;
};

#endif // TEXTEDITWIDGET_HPP
