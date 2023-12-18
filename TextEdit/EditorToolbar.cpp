#include "EditorToolBar.hpp"

#include <QPixmap>

EditorToolBar::EditorToolBar(QToolBar *parent)
    :QToolBar(parent)
{
    QAction* newFileAction = addAction(QPixmap(":/editor_icons/icons/newFile.png"),"new"); // add new file
    QAction* saveFileAction = addAction(QPixmap(":/editor_icons/icons/save.png"),"save"); // save file
    QAction* deleteFileAction = addAction(QPixmap(":/editor_icons/icons/delete.png"),"delete"); // delete file
    QAction* undoAction = addAction(QPixmap(":/editor_icons/icons/undo.png"),"undo"); // undo
    QAction* redoAction = addAction(QPixmap(":/editor_icons/icons/redo.png"),"redo"); // redo

    connect(newFileAction, &QAction::triggered, this, &EditorToolBar::newFileClicked);
    connect(saveFileAction, &QAction::triggered, this, &EditorToolBar::saveFileClicked);
    connect(deleteFileAction, &QAction::triggered, this, &EditorToolBar::deleteFileClicked);
    connect(undoAction, &QAction::triggered, this, &EditorToolBar::undoClicked);
    connect(redoAction, &QAction::triggered, this, &EditorToolBar::redoClicked);
}

void EditorToolBar::newFileClicked(){
    emit createNewFileSignal();
}

void EditorToolBar::saveFileClicked()
{
    emit saveFileSignal(); 
}

void EditorToolBar::deleteFileClicked()
{
    emit deleteFileSignal();
}

void EditorToolBar::undoClicked()
{
    emit undoSignal();
}

void EditorToolBar::redoClicked()
{
    emit redoSignal();
}
