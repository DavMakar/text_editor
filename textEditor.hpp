#ifndef TEXTEDITOR_HPP
#define TEXTEDITOR_HPP

#include <QWidget>

class TextEditor : public QWidget
{
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();
};
#endif // TEXTEDITOR_HPP
