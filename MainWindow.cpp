#include "MainWindow.hpp"
#include "Authentication/SignInWidget.hpp"
#include "Authentication/SignUpWidget.hpp"
#include "TextEdit/TextEditWidget.hpp"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, stkLayout(new QStackedLayout)
{
    setWindowTitle("Text Editor");
    setWindowIcon(QIcon(":/editor_icons/icons/newFile2.png"));

    SignInWidget* signInPage = new SignInWidget;
    SignUpWidget* signUpPage = new SignUpWidget;
    signInPage->setMinimumSize(widgetSize);
    signUpPage->setMinimumSize(widgetSize);

    stkLayout->addWidget(signInPage);
    stkLayout->addWidget(signUpPage);
    stkLayout->setCurrentIndex(0);

    QWidget *window = new QWidget;
    window->setLayout(stkLayout);
    setCentralWidget(window);

    connect(signInPage, &SignInWidget::signInSignal, this, &MainWindow::checkUser);
    connect(signInPage, &SignInWidget::signUpSignal, this, &MainWindow::showSignUp);
    connect(signUpPage, &SignUpWidget::createAccountSignal, this, &MainWindow::createUser);
}

void MainWindow::showSignIn()
{
    stkLayout->setCurrentIndex(0);
}

void MainWindow::showSignUp()
{
    stkLayout->setCurrentIndex(1);
}

void MainWindow::showTextEdit()
{
    stkLayout->setCurrentIndex(2);
}

void MainWindow::createUser(const QString& username, const QString& password)
{
    if(dataManager.addUser(username, password))
    {
        showSignIn();
        QMessageBox::information(this, "Success", "Successfully registered! Please sign in", QMessageBox::Ok);
    }
    else
    {
        qDebug() << "No account created";
    }
}

void MainWindow::logoutUser()
{
    stkLayout->removeWidget(stkLayout->currentWidget());
    showSignIn();
}

void MainWindow::checkUser(const QString &username, const QString &password)
{
    auto personId = dataManager.authenticateUser(username, password);
    if(personId)
    {
        userId = personId.value();
        TextEditWidget* textEdit = new TextEditWidget(userId, dataManager, this);
        textEdit->setMinimumSize(widgetSize);
        stkLayout->addWidget(textEdit);
        showTextEdit();
        connect(textEdit , &TextEditWidget::logoutSignal , this , &MainWindow::logoutUser);
    }
    else
    {
        QMessageBox::critical(this, "Error", "Wrong username or password", QMessageBox::Ok);
    }
}
