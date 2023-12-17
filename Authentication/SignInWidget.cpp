#include "SignInWidget.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialog>
#include <QFont>
#include <QPushButton>

SignInWidget::SignInWidget(QWidget *parent)
    : QWidget{parent}
{
    auto welcomeLabel = new QLabel("Welcome to Text Editor", this);
    welcomeLabel->setFont(QFont("Times", 18, QFont::Bold));
    welcomeLabel->setStyleSheet("color: CornflowerBlue");

    usernameLineEdit = new QLineEdit;
    usernameLineEdit->setFixedWidth(150);
    usernameLineEdit->setPlaceholderText("username");    

    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setFixedWidth(150);
    passwordLineEdit->setPlaceholderText("password");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    
    QPushButton* signInButton = new QPushButton("Sign in");
    QPushButton* signUpButton = new QPushButton("Sign up");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    mainLayout->setSpacing(75);
    mainLayout->addWidget(welcomeLabel,0,Qt::AlignmentFlag::AlignCenter);
    mainLayout->addWidget(usernameLineEdit,0,Qt::AlignmentFlag::AlignCenter);
    mainLayout->addWidget(passwordLineEdit,0,Qt::AlignmentFlag::AlignCenter);

    buttonLayout->addWidget(signInButton);
    buttonLayout->addWidget(signUpButton);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
    
    setLayout(mainLayout);

    connect(signInButton, &QPushButton::clicked , this , &SignInWidget::signInClicked);
    connect(signUpButton, &QPushButton::clicked , this , &SignInWidget::signUpClicked);
}

void SignInWidget::signInClicked()
{
    emit signInSignal(usernameLineEdit->text(), passwordLineEdit->text());
}

void SignInWidget::signUpClicked(){
    emit signUpSignal();
}
