#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

#include <QSqlDatabase>
#include <QString>


class DbManager
{
public:
    DbManager();
    ~DbManager();

    bool isOpen() const;
    bool createTable();
    void close();
    QSqlDatabase& getDb();
    bool addPerson(const QString& username,const QString& password);
    std::optional<int> personExists(const QString& username,const QString& password) const;

    QString getUserDocumentText(int id) const;
    bool setUserDocumentText(const QString& plainText,int id);
    bool removeAllPersons();

private:
    const QString path = "synopsys.db";
    QSqlDatabase m_db;
};
#endif // DBMANAGER_HPP
