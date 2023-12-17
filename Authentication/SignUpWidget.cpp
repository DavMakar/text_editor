#include "SignUpWidget.hpp"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

SignUpWidget::SignUpWidget(QWidget *parent)
    : QWidget{parent}
{
    auto signUpLabel = new QLabel("Sign Up", this);
    signUpLabel->setFont(QFont("Times", 18, QFont::Bold));
    signUpLabel->setStyleSheet("color: CornflowerBlue");

    usernameLineEdit = new QLineEdit;
    usernameLineEdit->setFixedWidth(150);
    usernameLineEdit->setPlaceholderText("username");    

    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setFixedWidth(150);
    passwordLineEdit->setPlaceholderText("password");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    
    confirmPasswordLineEdit = new QLineEdit;
    confirmPasswordLineEdit->setFixedWidth(150);
    confirmPasswordLineEdit->setPlaceholderText("password");
    confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton* createAccountButton = new QPushButton("create account");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(75);
    mainLayout->addWidget(signUpLabel,0,Qt::AlignmentFlag::AlignCenter);
    mainLayout->addWidget(usernameLineEdit,0,Qt::AlignmentFlag::AlignCenter);
    mainLayout->addWidget(passwordLineEdit,0,Qt::AlignmentFlag::AlignCenter);
    mainLayout->addWidget(confirmPasswordLineEdit,0,Qt::AlignmentFlag::AlignCenter);
    mainLayout->addWidget(createAccountButton,0,Qt::AlignmentFlag::AlignCenter);
    mainLayout->addStretch();
    
    setLayout(mainLayout);

    connect(createAccountButton,&QPushButton::clicked , this, &SignUpWidget::confirmUser);
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
