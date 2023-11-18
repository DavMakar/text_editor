#include "texteditwidget.hpp"
#include <QPushButton>
#include <QString>
#include <QListView>
#include <QItemSelectionModel>
#include <QStringList>
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

    QStringList columnNames = getColumnNameList();

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
                QModelIndexList deselectedIndexes = deselected.indexes();
                if(!deselectedIndexes.isEmpty()){
                    int deselectedColumn = deselectedIndexes.first().row();
                    updateTable(deselectedColumn + 1);  // stex harc a arajanum auto save
                        // te asenq qani hat column ka
                        // etqan textEdit pahenq
                }

                QModelIndexList selectedIndexes = selected.indexes();
                if (!selectedIndexes.isEmpty()) {
                    int selectedColumn = selectedIndexes.first().row();
                    QSqlRecord record = model_->record(0);
                    QVariant data = record.value(selectedColumn+1);
                    textEdit_->setText(data.toString());
                }
            });
}

QStringList TextEditWidget::getColumnNameList()
{
    QStringList columnNames;

    for(int i = 1; i < model_->columnCount() ; ++i){
        columnNames.push_back(getConcreteColumnName(i));
    }

    return columnNames;
}

void TextEditWidget::setText(const QString& plainText)
{
    textEdit_->setPlainText(plainText);
}

void TextEditWidget::setId(int id)
{
    userId_ = id;
}

QString TextEditWidget::getConcreteColumnName(int col)
{
    return model_->record().fieldName(col);
}

void TextEditWidget::updateTable(int col){
    model_->setData(model_->index(0,col),textEdit_->toPlainText());
    model_->submitAll();
}

void TextEditWidget::saveButtonClicked()
{
    emit saveSignal(textEdit_->toPlainText());
}
