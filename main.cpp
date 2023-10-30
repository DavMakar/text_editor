#include <QApplication>
#include <QDebug>
#include "userlogin.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);        
    UserLogin w;
    w.show();
    return a.exec();
}
