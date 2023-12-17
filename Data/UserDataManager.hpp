#ifndef USER_DATA_MANAGER_HPP
#define USER_DATA_MANAGER_HPP

#include <QSqlDatabase>

class UserDataManager
{
public:
    UserDataManager();
    ~UserDataManager();
    bool addUser(const QString& username, const QString& password);
    std::optional<int> authenticateUser(const QString& username,const QString& password) const;
    bool addFile(QString& filename, const QString& content , int userId);
    bool updateFile(const QString& filename, const QString& content , int userId);
    bool removeFile(const QString& filename, int userId);
    bool changeFilename(const QString& oldFilename, const QString& newFilename, int userId);
    QStringList getUserFilenames(int userId);
    QString getFileContent(const QString& filename,int userId);
private:
    QSqlDatabase db_;
};

#endif // USER_DATA_MANAGER_HPP
