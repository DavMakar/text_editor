#ifndef USERLOGIN_HPP
#define USERLOGIN_HPP

#include <QWidget>
#include <QLineEdit>

#include "dbmanager.hpp"

class UserLogin : public QWidget
{
    Q_OBJECT
public:
    explicit UserLogin(QWidget *parent = nullptr);

private slots:
    void searchUser();

private:
    DbManager db;
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
};

#endif // USERLOGIN_HPP
