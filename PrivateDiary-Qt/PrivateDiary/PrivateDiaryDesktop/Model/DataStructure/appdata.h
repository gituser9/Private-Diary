#ifndef APPDATA_H
#define APPDATA_H

#include <QString>

class AppData
{
public:

    void setUserPassword(const QString &password);
    QString getUserPassword() const;

    void setUserId(int id);
    int getUserId() const;


private:
    QString userPassword;
    int userId;
};

#endif // APPDATA_H
