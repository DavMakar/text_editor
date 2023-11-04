#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

#include <QWidget>
#include <QStackedLayout>
#include "dbmanager.hpp"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

private:
    DbManager db;
    QStackedLayout* stkLayout;

public slots:
    void showSignIn();
    void showSignUp();
    void checkUser(const QString& username, const QString& password);
    void createUser(const QString& username, const QString& password);
};

#endif // MAINWIDGET_HPP
