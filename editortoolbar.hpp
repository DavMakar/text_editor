#ifndef EDITORTOOLBAR_HPP
#define EDITORTOOLBAR_HPP

#include <QToolBar>

class EditorToolBar : public QToolBar
{
    Q_OBJECT
public:
    EditorToolBar(QToolBar* parent = nullptr);

private slots:
    void newFileClicked();
    void saveFileClicked();
    void deleteFileClicked();
    void undoClicked();
    void redoClicked();

signals:
    void createNewFileSignal();
    void saveFileSignal();
    void deleteFileSignal();
    void undoSignal();
    void redoSignal();
};

#endif // EDITORTOOLBAR_HPP
