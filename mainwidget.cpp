#include "mainwidget.hpp"
#include "userlogin.hpp"
#include "signupwidget.hpp"

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}, stkLayout{new QStackedLayout(this)}
{
    setWindowTitle("Text Editor");
    UserLogin* signInPage = new UserLogin(this);
    SignUpWidget* signUpPage = new SignUpWidget(this);

    stkLayout->addWidget(signInPage);
    stkLayout->addWidget(signUpPage);
    stkLayout->setCurrentIndex(0);

    setLayout(stkLayout);
    connect(signInPage,&UserLogin::signInSignal, this, &MainWidget::checkUser);
    connect(signInPage,&UserLogin::signUpSignal, this, &MainWidget::showSignUp);
    connect(signUpPage,&SignUpWidget::createAccountSignal, this, &MainWidget::createUser);
}

void MainWidget::showSignIn()
{
    stkLayout->setCurrentIndex(0);
}

void MainWidget::showSignUp(){
    stkLayout->setCurrentIndex(1);
}

void MainWidget::createUser(const QString& username, const QString& password){
    if(db.addPerson(username,password)){
        qDebug() << "account created succesfully";
        showSignIn();
        qDebug()<< "please login";
    }else{
        qDebug() << "no account created";
    }
}
void MainWidget::checkUser(const QString& username , const QString& password){
    if(db.personExists(username,password)){
        qDebug()<<"login succesfully";
    }
    else{
        qDebug()<<"user not found";
    }
}
