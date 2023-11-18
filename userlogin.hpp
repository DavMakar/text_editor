#ifndef USERLOGIN_HPP
#define USERLOGIN_HPP

#include <QWidget>
#include <QLineEdit>
#include "passwordmanager.hpp"

class UserLogin : public QWidget
{
    Q_OBJECT
public:
    explicit UserLogin(QWidget *parent = nullptr);

signals:
    void signInSignal(const QString& username,const QString& password);
    void signUpSignal();

private slots:
    void signInClicked();
    void signUpClicked();

private:
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
};

#endif // USERLOGIN_HPP
