#include "mainwidget.hpp"
#include "userlogin.hpp"
#include "signupwidget.hpp"
#include "texteditwidget.hpp"

#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}, stkWidget{new QStackedWidget(this)}
{
    setWindowTitle("Text Editor");
    UserLogin* signInPage = new UserLogin(this);
    SignUpWidget* signUpPage = new SignUpWidget(this);
    TextEditWidget* textEditPage = new TextEditWidget(this);

    stkWidget->addWidget(signInPage);
    stkWidget->addWidget(signUpPage);
    stkWidget->addWidget(textEditPage);

    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(stkWidget);

    setLayout(vLayout);
    connect(signInPage,&UserLogin::signInSignal, this, &MainWidget::checkUser);
    connect(signInPage,&UserLogin::signUpSignal, this, &MainWidget::showSignUp);
    connect(signUpPage,&SignUpWidget::createAccountSignal, this, &MainWidget::createUser);
    connect(textEditPage,&TextEditWidget::saveSignal, this, &MainWidget::saveText);
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
    if(db.addPerson(username,password)){
        qDebug() << "account created succesfully";
        showSignIn();
        qDebug()<< "please login";
    }else{
        qDebug() << "no account created";
    }
}

void MainWidget::checkUser(const QString& username , const QString& password){
    auto personId = db.personExists(username,password);
    if(personId){
        userId = personId.value();
        showTextEdit();
        QWidget *currentWidget = stkWidget->currentWidget();
        TextEditWidget* textEdit = qobject_cast<TextEditWidget*>(currentWidget);
        if(textEdit){
            qDebug()<<"exav";
            textEdit->setText(db.getUserDocumentText(userId));
        }else{
            qDebug()<< "chexav";
        }
    }else{
        qDebug()<< "wrong username or password!!!";
    }
}

void MainWidget::saveText(const QString& plainText){
    if(db.setUserDocumentText(plainText,userId)){
        qDebug() << "saved to db";
    }else{
        qDebug() << "error can't save";
    }
}
