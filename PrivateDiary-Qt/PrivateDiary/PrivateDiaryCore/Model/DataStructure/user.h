#ifndef USER_H
#define USER_H

#include <QString>


struct User {
public:
    int id;
    QString login;
    QString password;

    User() {
        id = 0;
        login = "";
        password = "";
    }
};

#endif // USER_H
