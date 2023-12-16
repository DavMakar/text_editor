#include "PasswordManager.hpp"

QString  PasswordManager::encrypt(QString password)
{
    QByteArray byteArrayPass = password.toUtf8();

    QByteArray  hashedPass = QCryptographicHash::hash(byteArrayPass, algo);

    return hashedPass.toHex();
}

bool PasswordManager::isEqualPasswords(QString pass1, QString hashedPass2)
{
    QString hashedPass1 = encrypt(pass1);
    return (hashedPass1 == hashedPass2);
}
