#include "TextEditWidget.hpp"

#include <QString>
#include <QListView>
#include <QLineEdit>
#include <QItemSelectionModel>
#include <QStringList>
#include <QStringListModel>
#include <QGridLayout>
#include <QStringLiteral>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "../Data/UserDataManager.hpp"
#include "FileNameDelegate.hpp"
#include "EditorToolbar.hpp"
#include "LogoutToolbar.hpp"

TextEditWidget::TextEditWidget(int id, UserDataManager& db ,QWidget *parent)
    : userId_(id), db(db), textEdit_{new QTextEdit(this)},QWidget{parent}
{
    EditorToolBar* editBar = new EditorToolBar;
    LogoutToolBar* logoutBar = new LogoutToolBar;

    QString initialFilename = QStringLiteral("Untitled");
    QStringList userFilenames = db.getUserFilenames(userId_);

    if(userFilenames.isEmpty()){
        db.addFile(initialFilename,"",userId_);
        userFilenames << initialFilename;
    }

    slModel_ = new QStringListModel(userFilenames,this);

    FilenameDelegate* flnameDelegate = new FilenameDelegate;

    QListView* flnameView = new QListView(this); /// TODO FilenameView class
    flnameView->setModel(slModel_);
    flnameView->setFixedWidth(100);
    flnameView->setItemDelegate(flnameDelegate);

    selectionModel = new QItemSelectionModel(slModel_);
    flnameView->setSelectionModel(selectionModel);

    QHBoxLayout* toolbarLayout = new QHBoxLayout();
    toolbarLayout->addWidget(editBar);
    toolbarLayout->addWidget(logoutBar,0,Qt::AlignRight);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(flnameView);
    hlayout->addWidget(textEdit_);

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setSpacing(5);
    vlayout->setContentsMargins(0,0,0,0);
    vlayout->addLayout(toolbarLayout);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    connect(editBar,&EditorToolBar::createNewFileSignal,this,&TextEditWidget::createNewFileSlot);
    connect(editBar,&EditorToolBar::saveFileSignal,this,&TextEditWidget::saveFileSlot);
    connect(editBar,&EditorToolBar::deleteFileSignal,this,&TextEditWidget::deleteSlot);
    connect(editBar,&EditorToolBar::undoSignal,this,&TextEditWidget::undoSlot);
    connect(editBar,&EditorToolBar::redoSignal,this,&TextEditWidget::redoSlot);
    connect(logoutBar,&LogoutToolBar::logoutSignal,this,&TextEditWidget::logoutSlot);

    connect(flnameView,&QListView::doubleClicked , this , &TextEditWidget::setOldFilenameSlot);
    connect(flnameDelegate,&FilenameDelegate::commitData , this , &TextEditWidget::updateFilenameSlot);
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

/// SLOTS

void TextEditWidget::setOldFilenameSlot(const QModelIndex &index)
{
    oldFilename = filenameFromIndex(index);
}

void TextEditWidget::updateFilenameSlot(QWidget* editor)
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if(lineEdit){
        db.changeFilename(oldFilename,lineEdit->text(),userId_);
    }
}

void TextEditWidget::selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList deselectedIndexes = deselected.indexes();
    if(!deselectedIndexes.isEmpty()){
        QString deselectedFilename = filenameFromIndex(deselectedIndexes.first());
        db.updateFile(deselectedFilename,textEdit_->toPlainText(), userId_);
    }
    QModelIndexList selectedIndexes = selected.indexes();
    if (!selectedIndexes.isEmpty()) {
        QString selectedFilename = filenameFromIndex(selectedIndexes.first());
        QString fileContent = db.getFileContent(selectedFilename,userId_);
        textEdit_->setText(fileContent);
    }
}

void TextEditWidget::createNewFileSlot()
{
    QString filename = "Untitled";
    db.addFile(filename,"",userId_);
    slModel_->insertRow(slModel_->rowCount());
    QModelIndex index = slModel_->index(slModel_->rowCount()-1);
    slModel_->setData(index,filename);
}

void TextEditWidget::saveFileSlot()
{
    db.updateFile(filenameFromIndex(selectionModel->currentIndex()),textEdit_->toPlainText(),userId_);
}

void TextEditWidget::deleteSlot()
{
    QModelIndex index = selectionModel->currentIndex();
    if(index.isValid()){
        db.removeFile(filenameFromIndex(index),userId_);
        slModel_->removeRows(index.row(),1);
    }
}

void TextEditWidget::undoSlot()
{
    textEdit_->undo();
}

void TextEditWidget::redoSlot()
{
    textEdit_->redo();
}

void TextEditWidget::logoutSlot()
{
    emit logoutSignal();
}
