#ifndef SIGN_IN_WIDGET_HPP
#define SIGN_IN_WIDGET_HPP

#include <QWidget>
#include <QLineEdit>

class SignInWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SignInWidget(QWidget *parent = nullptr);

signals:
    void signInSignal(const QString& username,const QString& password);
    void signUpSignal();

private slots:
    void signInClicked();
    void signUpClicked();

private:
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
};

#endif // SIGN_IN_WIDGET_HPP
