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

private:
    const QSize widgetSize{400, 300};
    int userId;
    UserDataManager dataManager;
    QStackedLayout* stkLayout;

public slots:
    //void saveText(const QString& text);
    void showSignIn();
    void showSignUp();
    void showTextEdit();
    void checkUser(const QString& username, const QString& password);
    void createUser(const QString& username, const QString& password);
};

#endif // MAINWINDOW_HPP
