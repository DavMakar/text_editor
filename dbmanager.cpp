#include "dbmanager.hpp"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

DbManager::DbManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(!m_db.open()){
        qDebug()<< "Error: no connection";
    }
    else{
        qDebug()<< "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE people(id INTEGER PRIMARY KEY, name TEXT);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'people': one might already exist.";
        success = false;
    }

    return success;
}

void DbManager::close()
{
    m_db.close();
}

QSqlDatabase &DbManager::getDb()
{
    return m_db;
}

bool DbManager::addPerson(const QString& username,const QString& password)
{
    bool success = false;

    if (!username.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO people (username,password) VALUES (:username,:password)");
        queryAdd.bindValue(":username", username);
        queryAdd.bindValue(":password", password);

        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add person failed: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add person failed: name cannot be empty";
    }

    return success;
}

QString DbManager::getUserDocumentText(int id) const
{
    QSqlQuery query;
    query.prepare("SELECT document FROM people WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();
    if (query.first())
    {
        return query.value(0).toString();
    }
    qDebug() << "Query execution error: " << query.lastError().text();
    return "";
}


bool DbManager::setUserDocumentText(const QString &plainText, int id)
{
    QSqlQuery setQuery;
    setQuery.prepare("UPDATE people SET document = :userText WHERE id = :userId");
    setQuery.bindValue(":userText", plainText);
    setQuery.bindValue(":userId", id);

    return setQuery.exec();
}

std::optional<int> DbManager::personExists(const QString& username, const QString& password) const
{
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM people WHERE username = (:username) AND password = (:password)");
    checkQuery.bindValue(":username", username);
    checkQuery.bindValue(":password", password);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            return checkQuery.value(0).toInt();
        }
    }
    else
    {
        qDebug() << "person exists failed: " << checkQuery.lastError();
    }

    return std::nullopt;
}

bool DbManager::removeAllPersons()
{
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM people");

    if (removeQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "remove all persons failed: " << removeQuery.lastError();
    }

    return success;
}
