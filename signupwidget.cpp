#include "signupwidget.hpp"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

SignUpWidget::SignUpWidget(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* VLayout = new QVBoxLayout(this);

    QLabel* usernameLabel = new QLabel("Username : ");
    QLabel* passwordLabel = new QLabel("Password : ");
    QLabel* confirmPasswordLabel = new QLabel("Confirm Password : ");

    usernameLineEdit = new QLineEdit;
    usernameLineEdit->setPlaceholderText("login");
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setPlaceholderText("password");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordLineEdit = new QLineEdit;
    confirmPasswordLineEdit->setPlaceholderText("password");
    confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton* createAccount = new QPushButton("create account");
    VLayout->addWidget(usernameLabel);
    VLayout->addWidget(usernameLineEdit);
    VLayout->addWidget(passwordLabel);
    VLayout->addWidget(passwordLineEdit);
    VLayout->addWidget(confirmPasswordLabel);
    VLayout->addWidget(confirmPasswordLineEdit);
    VLayout->addSpacing(15);
    VLayout->addWidget(createAccount);

    setLayout(VLayout);

    connect(createAccount,&QPushButton::clicked , this, &SignUpWidget::confirmUser);
}

void SignUpWidget::confirmUser()
{
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();
    QString confirmPassword = confirmPasswordLineEdit->text();

    if(password == confirmPassword){
        emit createAccountSignal(username,password);
    }
    else{
        qDebug() << "passwords don't match";
    }
}
