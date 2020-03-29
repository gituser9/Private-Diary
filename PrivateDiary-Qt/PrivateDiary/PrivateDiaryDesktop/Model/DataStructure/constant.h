#ifndef CONSTANT_H
#define CONSTANT_H

#include <QString>
#include <QDir>


namespace Constant {
    const QString defaultTitle = "New Post";
    const QString dbName = "PrivateDiary.dbx";
    const QString dbPath = QDir::homePath() + "/" + dbName;

    namespace UserFields {
        const QString login = "login";
        const QString password = "password";
        const QString id = "id";
    };

    namespace PostFields {
        const QString date = "date";
        const QString title = "title";
        const QString body = "body";
        const QString id = "id";
    }
}





#endif // CONSTANT_H
