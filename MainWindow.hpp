#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStackedLayout>
#include "Data/UserDataManager.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void showTextEdit();
    void showSignIn();

public slots:
    void showSignUp();    
    void logoutUser();
    void checkUser(const QString& username, const QString& password);
    void createUser(const QString& username, const QString& password);
    
private:
    const QSize widgetSize{400, 300};
    int userId;
    UserDataManager dataManager;
    QStackedLayout* stkLayout;
};

#endif // MAINWINDOW_HPP
