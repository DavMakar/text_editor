#include "texteditwidget.hpp"
#include <QPushButton>
#include <QString>
#include <QListView>
#include <QItemSelectionModel>
#include <QStringList>
#include <QStringListModel>
#include <QSqlRecord>
#include <QGridLayout>

TextEditWidget::TextEditWidget(int id, QSqlDatabase& db ,QWidget *parent)
    : userId_(id), db_(db), textEdit_{new QTextEdit(this)},QWidget{parent}
{
    textEdit_->setFixedSize(400,300);


    QString tableName = QStringLiteral("user%1").arg(userId_);

    model_ = new QSqlTableModel(this,db_);
    model_->setTable(tableName);
    model_->select();

    QStringList columnNames;
    for(int i = 1; i < model_->columnCount() ; ++i){
        columnNames.push_back(getColumnName(i));
    }

    QStringListModel* slModel = new QStringListModel(columnNames,this);

    QListView *listView = new QListView(this);
    listView->setModel(slModel);

    QItemSelectionModel* selectionModel = new QItemSelectionModel(slModel);
    listView->setSelectionModel(selectionModel);

    QPushButton* saveButton = new QPushButton("Save", this);

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setHorizontalSpacing(10);
    gridLayout->addWidget(listView, 0, 0, 1, 1);
    gridLayout->addWidget(textEdit_, 0, 1, 1, 1);
    gridLayout->addWidget(saveButton, 1, 1, 1, 1);

    setLayout(gridLayout);

    connect(saveButton,&QPushButton::clicked, this, &TextEditWidget::saveButtonClicked);
    connect(selectionModel,&QItemSelectionModel::selectionChanged,
    [=](const QItemSelection &selected, const QItemSelection &deselected){
        QModelIndexList indexes = selectionModel->selectedIndexes();
        if (!indexes.isEmpty()) {
            int selectedColumn = indexes.first().row();
            QSqlRecord record = model_->record(0);
            QVariant data = record.value(selectedColumn+1);
            textEdit_->setText(data.toString());
        }
    });
}

void TextEditWidget::setText(const QString& plainText)
{
    textEdit_->setPlainText(plainText);
}

void TextEditWidget::setId(int id)
{
    userId_ = id;
}

QString TextEditWidget::getColumnName(int col)
{
    return model_->record().fieldName(col);
}

void TextEditWidget::saveButtonClicked()
{
    emit saveSignal(textEdit_->toPlainText());
}
