#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <QString>
#include <QtSql>
#include <QCryptographicHash>

#include "Model/DataStructure/constant.h"
#include "Model/DataStructure/appdata.h"


class UserService
{
public:
    UserService();

    bool registration(const QString &login, const QString &password);
    bool auth(const QString &login, const QString &password);

    void setAppData(std::shared_ptr<AppData> appData);

private:
    std::shared_ptr<AppData> appData;

    QSqlDatabase getDb();
    QString hashPassword(const QString &password) const;
    void initDatabase();
};

#endif // USERSERVICE_H
