#include "appdata.h"


void AppData::setUserPassword(const QString &password)
{
    userPassword = password;
}

QString AppData::getUserPassword() const
{
    return userPassword;
}

void AppData::setUserId(int id)
{
    userId = id;
}

int AppData::getUserId() const
{
    return userId;
}
