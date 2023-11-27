#ifndef DBFACADE_HPP
#define DBFACADE_HPP

#include <QSqlDatabase>


class DBFacade
{
public:
    DBFacade();
    ~DBFacade();
    bool addUser(const QString& username, const QString& password);
    std::optional<int> authenticateUser(const QString& username,const QString& password) const;
    bool addFile(const QString& filename, const QString& content , int userId);
    bool updateFile(const QString& filename, const QString& content , int userId);
    bool removeFile(const QString& filename, int userId);
    bool changeFilename(const QString& oldFilename, const QString& newFilename, int userId);
    QStringList getUserFilenames(int userId);
    QString getFileContent(const QString& filename,int userId);
private:
    QSqlDatabase db_;
};

#endif // DBFACADE_HPP
