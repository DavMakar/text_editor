#include "userlogin.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QDialog>
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

    QHBoxLayout* HButtonLayout = new QHBoxLayout();
    HButtonLayout->addWidget(signIn);
    HButtonLayout->addStretch(1);
    HButtonLayout->addWidget(signUp);

    VLayout->addWidget(usernameLabel);
    VLayout->addWidget(usernameLineEdit);
    VLayout->addWidget(passwordLabel);
    VLayout->addWidget(passwordLineEdit);
    VLayout->addSpacing(15);
    VLayout->addLayout(HButtonLayout);

    setLayout(VLayout);

    connect(signIn, &QPushButton::clicked , this , &UserLogin::signInClicked);
    connect(signUp, &QPushButton::clicked , this , &UserLogin::signUpClicked);
}

void UserLogin::signInClicked()
{
    emit signInSignal(usernameLineEdit->text(), passwordLineEdit->text());
}

void UserLogin::signUpClicked(){
    emit signUpSignal();
}
