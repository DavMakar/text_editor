#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <QCryptographicHash>
#include <QByteArray>
#include <QString>

class PasswordManager
{
public:
    static QString  encrypt(QString password);
    static bool isEqualPasswords(QString pass1, QString hashedPass2);
private:
    static const  QCryptographicHash::Algorithm   algo = QCryptographicHash::Algorithm::Sha224;
};

#endif // PASSWORDMANAGER_H
