#ifndef LOGOUT_TOOLBAR_HPP
#define LOGOUT_TOOLBAR_HPP
#include <QToolBar>

class LogoutToolBar : public QToolBar
{
    Q_OBJECT
public:
    LogoutToolBar(QToolBar* parent = nullptr);

private slots:
    void logoutClicked();

signals:
    void logoutSignal();
};

#endif //LOGOUT_TOOLBAR_HPP