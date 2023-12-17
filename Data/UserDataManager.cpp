#include "UserDataManager.hpp"
#include <QSqlQuery>
#include <QSqlError>
#include "PasswordManager.hpp"

UserDataManager::UserDataManager()
{
    db_ = QSqlDatabase::addDatabase("QSQLITE");
    db_.setDatabaseName("synopsys.db");

    if(!db_.open()){
        qDebug()<< "Error: no connection";
    }
    else{
        qDebug()<< "Database: connection established";
    }
}

UserDataManager::~UserDataManager()
{
    if(db_.isOpen()){
        db_.close();
    }
}

bool UserDataManager::addUser(const QString &username, const QString &password)
{
    if(!username.isEmpty()){
        QSqlQuery query;
        QString encryptedPassword = PasswordManager::encrypt(password);
        query.prepare("INSERT INTO users (username,password) VALUES (:username,:password)");
        query.bindValue(":username",username);
        query.bindValue(":password",encryptedPassword);

        if(query.exec()){
            return true;
        }
        else{
            qDebug() << "add user failed " << query.lastError();
        }
    }
    else{
        qDebug() << "username empty , add user failed";
    }
    return false;
}

std::optional<int> UserDataManager::authenticateUser(const QString &username, const QString &password) const
{
    QSqlQuery checkQuery;

    QString encryptedPassword = PasswordManager::encrypt(password);

    checkQuery.prepare("SELECT userId FROM users WHERE username = (:username) "
                       "AND password = (:password)");
    checkQuery.bindValue(":username", username);
    checkQuery.bindValue(":password", encryptedPassword);

    if (checkQuery.exec()){
        if(checkQuery.next())
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
/////////////////////////////////////////////////////////////////////////////////////////////
bool UserDataManager::addFile(QString &filename, const QString &content, int userId)
{
    QStringList filenamesOfUser = getUserFilenames(userId);

    QString tempFileName = QString(filename);
    for (size_t index = 0; ; ++index)
    {
        if (std::find(filenamesOfUser.begin(), filenamesOfUser.end(), tempFileName) == filenamesOfUser.end())
        {
            break;
        }
        tempFileName = filename + QString("(") + QString::number(index) + QString(")");
    }
	filename = tempFileName;

    QSqlQuery query;
    query.prepare("INSERT INTO user_files (filename,content,userId) VALUES (:filename,:content,:userId)");
    query.bindValue(":filename", filename);
    query.bindValue(":content", content);
    query.bindValue(":userId", userId);

    if (query.exec())
    {
        return true;
    }
    else
    {
        qDebug() << "add file failed" << query.lastError();
    }
    return false;
}

bool UserDataManager::updateFile(const QString &filename, const QString &content, int userId)
{
    QSqlQuery query;
    query.prepare("UPDATE user_files SET content = (:content)"
                  "WHERE filename = (:filename) AND userId = (:userId)");
    query.bindValue(":content",content);
    query.bindValue(":filename",filename);
    query.bindValue(":userId",userId);

    if(query.exec()){
        return true;
    }else{
        qDebug()<< "fail to update file" << query.lastError();
    }
    return false;
}

bool UserDataManager::removeFile(const QString &filename, int userId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM user_files WHERE filename = (:filename) AND userId = (:userId)");
    query.bindValue(":filename" , filename);
    query.bindValue(":userId" , userId);

    if(query.exec()){
        return true;
    }
    else{
        qDebug() << "remove file failed" << query.lastError();
    }
    return false;
}

bool UserDataManager::changeFilename(const QString &oldFilename, const QString &newFilename, int userId)
{
    QSqlQuery query;
    query.prepare("UPDATE user_files SET filename = (:newFilename)"
                  "WHERE filename = (:oldFilename) AND userId = (:userId)");
    query.bindValue(":newFilename", newFilename);
    query.bindValue(":oldFilename", oldFilename);
    query.bindValue(":userId", userId);

    if(query.exec()){
        return true;
    }else{
        qDebug()<< "fail to changeFilename" << query.lastError();
    }
    return false;
    
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
QStringList UserDataManager::getUserFilenames(int userId)
{
    QStringList filenames;
    QSqlQuery query;
    query.prepare("SELECT filename FROM user_files WHERE userId = (:userId)");
    query.bindValue(":userId", userId);

    if (query.exec()) {
        while (query.next()) {
            filenames.append(query.value(0).toString());
        }
    } else {
        qDebug() << "Error getting filenames:" << query.lastError();
    }
    return filenames;
}

QString UserDataManager::getFileContent(const QString &filename, int userId)
{
    QString content;
    QSqlQuery query;
    query.prepare("SELECT content FROM user_files WHERE userId = (:userId) "
                  "AND filename = (:filename)");
    query.bindValue(":userId",userId);
    query.bindValue(":filename",filename);

    if (query.exec() && query.next()) {
        content = query.value(0).toString();
    }
    else
    {
        qDebug() << "Error getting file content:" << query.lastError();
    }
    return content;
}

//QSqlTableModel* UserDataManager::getUserFilenameModel()
//{
//    QSqlTableModel* model = new QSqlTableModel(nullptdb)
//}

