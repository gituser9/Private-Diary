#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <memory>

#include <QString>
#include <QtSql>
#include <QCryptographicHash>

#include "Model/DataStructure/constant.h"
#include "Model/DataStructure/appdata.h"
#include "Model/DataStructure/post.h"
#include <Util/crypter.h>


class UserService
{
public:
    UserService();

    bool registration(const QString &login, const QString &password);
    bool auth(const QString &login, const QString &password);
    bool update(const QString &login, const QString &password);

    void setAppData(std::shared_ptr<AppData> appData);

private:
    std::shared_ptr<AppData> appData;
    Crypter crypter;

    QSqlDatabase getDb();
    QString hashPassword(const QString &password) const;
    void initDatabase();
    bool recryptedPosts(const QString &newPassword);
};

#endif // USERSERVICE_H
