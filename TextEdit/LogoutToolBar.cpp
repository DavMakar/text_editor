#include "LogoutToolBar.hpp"
#include <QPixmap>

LogoutToolBar::LogoutToolBar(QToolBar *parent)
    :QToolBar(parent)
{
    QAction* logoutAction = addAction(QPixmap(":/logout_icons/icons/logout.png"),"logout");
    connect(logoutAction, &QAction::triggered, this, &LogoutToolBar::logoutClicked);
}

void LogoutToolBar::logoutClicked(){
    emit logoutSignal();
}
