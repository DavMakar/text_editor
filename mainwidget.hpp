#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

#include <QWidget>
#include <QStackedWidget>
#include "dbfacade.hpp"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

private:
    int userId;
    UserDataManager dbFacade;
    QStackedWidget* stkWidget;

public slots:
    //void saveText(const QString& text);
    void showSignIn();
    void showSignUp();
    void showTextEdit();
    void checkUser(const QString& username, const QString& password);
    void createUser(const QString& username, const QString& password);
};

#endif // MAINWIDGET_HPP
