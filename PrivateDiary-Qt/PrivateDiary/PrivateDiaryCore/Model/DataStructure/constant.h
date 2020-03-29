#ifndef CONSTANT_H
#define CONSTANT_H

#include <QString>
#include <QDir>
#include <QStandardPaths>


namespace Constant {
    const QString defaultTitle = "New Post";
    const QString dbName = "PrivateDiary.dbx";

#ifdef Q_OS_MACOS
    const QString dbPath = QDir::homePath() + "/" + dbName;
#endif
#ifdef Q_OS_WIN
    const QString dbPath = QDir::homePath() + "/" + dbName;
#endif
#ifdef Q_OS_LINUX
    const QString dbPath = QDir::homePath() + "/" + dbName;
#endif
#ifdef Q_OS_ANDROID
    const QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#endif
#ifdef Q_OS_IOS
    const QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#endif

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
