#include "mainwidget.hpp"
#include "userlogin.hpp"
#include "signupwidget.hpp"
#include "texteditwidget.hpp"
#include <QVBoxLayout>
#include <QIcon>

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}, stkWidget{new QStackedWidget(this)}
{
    setWindowTitle("Text Editor");
    setWindowIcon(QIcon(":/editor_icons/icons/newFile2.png"));

    // Move Widget on the screen center

    UserLogin* signInPage = new UserLogin(this);
    SignUpWidget* signUpPage = new SignUpWidget(this);

    stkWidget->addWidget(signInPage);
    stkWidget->addWidget(signUpPage);

    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(stkWidget);

    setLayout(vLayout);
    connect(signInPage,&UserLogin::signInSignal, this, &MainWidget::checkUser);
    connect(signInPage,&UserLogin::signUpSignal, this, &MainWidget::showSignUp);
    connect(signUpPage,&SignUpWidget::createAccountSignal, this, &MainWidget::createUser);

}

void MainWidget::showSignIn()
{
    stkWidget->setCurrentIndex(0);
}

void MainWidget::showSignUp(){
    stkWidget->setCurrentIndex(1);
}

void MainWidget::showTextEdit(){
    stkWidget->setCurrentIndex(2);
}

void MainWidget::createUser(const QString& username, const QString& password){
    if(dbFacade.addUser(username,password)){
        qDebug() << "account created succesfully";
        showSignIn();
        qDebug()<< "please login";
    }else{
        qDebug() << "no account created";
    }
}

void MainWidget::checkUser(const QString& username , const QString& password){
    auto personId = dbFacade.authenticateUser(username,password);
    if(personId){
        userId = personId.value();
        TextEditWidget* textEdit = new TextEditWidget(userId, dbFacade ,this);
        stkWidget->addWidget(textEdit);
        showTextEdit();
    }else{
        qDebug()<< "wrong username or password!!!";
    }
}
