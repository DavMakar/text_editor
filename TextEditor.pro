QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Authentication/SignUpWidget.cpp \
    Authentication/SignInWidget.cpp \
    Data/UserDataManager.cpp \
    Data/PasswordManager.cpp \
    TextEdit/EditorToolbar.cpp \
    TextEdit/FileNameDelegate.cpp \
    TextEdit/TextEditWidget.cpp \

HEADERS += \
    MainWindow.hpp \
   	Authentication/SignUpWidget.hpp \
    Authentication/SignInWidget.hpp \
    Data/UserDataManager.hpp \
    Data/PasswordManager.hpp \
    TextEdit/EditorToolbar.hpp \
    TextEdit/FileNameDelegate.hpp \
    TextEdit/TextEditWidget.hpp \
    
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
