#include "texteditwidget.hpp"
#include <QPushButton>
#include <QString>
#include <QListView>
#include <QItemSelectionModel>
#include <QStringList>
#include <QStringListModel>
#include <QSqlRecord>
#include <QGridLayout>
#include "dbfacade.hpp"

TextEditWidget::TextEditWidget(int id, DBFacade& dbFacade ,QWidget *parent)
    : userId_(id), dbFacade(dbFacade), textEdit_{new QTextEdit(this)},QWidget{parent}
{
    textEdit_->setFixedSize(400,300);

    QStringList userFilenames = dbFacade.getUserFilenames(userId_);
    if(userFilenames.isEmpty()){
        dbFacade.addFile("unknown","",userId_);
        userFilenames << "unknown";
    }

    slModel_ = new QStringListModel(userFilenames,this);

    QListView *listView = new QListView(this);
    listView->setModel(slModel_);

    selectionModel = new QItemSelectionModel(slModel_);
    listView->setSelectionModel(selectionModel);

    QPushButton* saveButton = new QPushButton("Save", this);

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setHorizontalSpacing(10);
    gridLayout->addWidget(listView, 0, 0, 1, 1);
    gridLayout->addWidget(textEdit_, 0, 1, 1, 1);
    gridLayout->addWidget(saveButton, 1, 1, 1, 1);

    setLayout(gridLayout);

    connect(saveButton,&QPushButton::clicked, this, &TextEditWidget::saveButtonClicked);
    connect(selectionModel,&QItemSelectionModel::selectionChanged , this , &TextEditWidget::selectionChangedSlot);
}

void TextEditWidget::setText(const QString& plainText)
{
    textEdit_->setPlainText(plainText);
}

void TextEditWidget::setId(int id)
{
    userId_ = id;
}

QString TextEditWidget::filenameFromIndex(const QModelIndex &index)
{
    if(index.isValid()){
        return slModel_->data(index, Qt::DisplayRole).toString();
    }
    return QString();
}


void TextEditWidget::saveButtonClicked()
{
    dbFacade.updateFile(filenameFromIndex(selectionModel->currentIndex()),textEdit_->toPlainText(),userId_);
}

void TextEditWidget::selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList deselectedIndexes = deselected.indexes();
    if(!deselectedIndexes.isEmpty()){
        QString deselectedFilename = filenameFromIndex(deselectedIndexes.first());
        dbFacade.updateFile(deselectedFilename,textEdit_->toPlainText(), userId_);
    }
    QModelIndexList selectedIndexes = selected.indexes();
    if (!selectedIndexes.isEmpty()) {
        QString selectedFilename = filenameFromIndex(selectedIndexes.first());
        QString fileContent = dbFacade.getFileContent(selectedFilename,userId_);
        textEdit_->setText(fileContent);
    }
}
