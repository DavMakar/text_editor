#ifndef SIGNUPWIDGET_HPP
#define SIGNUPWIDGET_HPP

#include <QWidget>
#include <QLineEdit>

class SignUpWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SignUpWidget(QWidget *parent = nullptr);

signals:
    void createAccountSignal(const QString& username,const QString& password);

public slots:
    void confirmUser();

private:
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QLineEdit* confirmPasswordLineEdit;
};

#endif // SIGNUPWIDGET_HPP
