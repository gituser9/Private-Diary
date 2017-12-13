#ifndef CONSTANT_H
#define CONSTANT_H

#include <QString>


namespace Constant {
    const QString defaultTitle = "New Post";
    const QString dbName = "PrivateDiary.dbx";

    namespace UserFields {
        const QString login = "login";
        const QString password = "password";
        const QString id = "id";
    };
}





#endif // CONSTANT_H
