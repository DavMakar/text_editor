#include "userlogin.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>


UserLogin::UserLogin(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* VLayout = new QVBoxLayout(this);

    QLabel* usernameLabel = new QLabel("Username : ");
    QLabel* passwordLabel = new QLabel("Password : ");

    usernameLineEdit = new QLineEdit;
    usernameLineEdit->setPlaceholderText("login");
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setPlaceholderText("password");
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton* signIn = new QPushButton("Sign in");
    QPushButton* signUp = new QPushButton("Sign up");

    QHBoxLayout* HButtonLayout = new QHBoxLayout(this);
    HButtonLayout->addWidget(signIn);
    HButtonLayout->addWidget(signUp);

    QGroupBox* buttonsGroup = new QGroupBox(this);
    buttonsGroup->setLayout(HButtonLayout);

    VLayout->addWidget(usernameLabel);
    VLayout->addWidget(usernameLineEdit);
    VLayout->addWidget(passwordLabel);
    VLayout->addWidget(passwordLineEdit);
    VLayout->addWidget(buttonsGroup);

    setLayout(VLayout);

    connect(signIn, &QPushButton::clicked , this , &UserLogin::searchUser);
}

void UserLogin::searchUser()
{
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    if(db.personExists(username,password)){
        qDebug()<<"user found";
    }
    else{
        qDebug()<<"not found";
    }
}
