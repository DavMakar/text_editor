#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

#include <QSqlDatabase>

class DbManager
{
public:
    DbManager();
    ~DbManager();

    bool isOpen() const;
    bool createTable();

    bool addPerson(const QString& username,const QString& password);
    bool personExists(const QString& username,const QString& password) const;

    void printAllPersons() const;
    bool removeAllPersons();

private:
    const QString path = "synopsys.db";
    QSqlDatabase m_db;
};
#endif // DBMANAGER_HPP
