#include "texteditwidget.hpp"
#include <QVBoxLayout>
#include <QPushButton>

TextEditWidget::TextEditWidget(QWidget *parent)
    : QWidget{parent},textEdit_{new QTextEdit(this)}
{
    QVBoxLayout* vLayout = new QVBoxLayout(this);
    vLayout->addWidget(textEdit_);

    QPushButton* saveButton = new QPushButton("Save", this);
    vLayout->addWidget(saveButton);

    connect(saveButton,&QPushButton::clicked, this, &TextEditWidget::saveButtonClicked);
}

void TextEditWidget::setText(const QString& plainText)
{
    textEdit_->setPlainText(plainText);
}

void TextEditWidget::saveButtonClicked()
{
    emit saveSignal(textEdit_->toPlainText());
}
