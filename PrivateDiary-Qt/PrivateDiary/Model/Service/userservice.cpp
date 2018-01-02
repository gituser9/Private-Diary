#include "userservice.h"


UserService::UserService()
{
    initDatabase();
}

bool UserService::registration(const QString &login, const QString &password)
{
    auto db = getDb();
    QSqlQuery query;
    query.prepare("select count(*) from users where login=?");
    query.addBindValue(login);

    if (!query.exec()) {
        return false;
    }

    query.next();
    int count = query.value(0).toInt();

    if (count != 0) {
        return false;
    }

    QString hashedPassword = hashPassword(password);
    query.prepare("insert into users(login, password) values(?, ?)");
    query.addBindValue(login);
    query.addBindValue(hashedPassword);
    bool result = query.exec();

    query.prepare("select id from users where login=? and password=?");
    query.addBindValue(login);
    query.addBindValue(hashedPassword);
    query.exec();
    query.next();
    appData->setUserId(query.value(Constant::UserFields::id).toInt());

    db.close();

    return result;
}

bool UserService::auth(const QString &login, const QString &password)
{
    auto db = getDb();
    QString hashedPassword = hashPassword(password);
    QSqlQuery query;
    query.prepare("select id from users where login=? and password=?");
    query.addBindValue(login);
    query.addBindValue(hashedPassword);

    if (!query.exec()) {
        return false;
    }

    query.next();
    int id = query.value(Constant::UserFields::id).toInt();
    bool result = id != 0;
    appData->setUserId(id);

    db.close();

    return result;
}

void UserService::setAppData(std::shared_ptr<AppData> appData)
{
    this->appData = appData;
}

QSqlDatabase UserService::getDb()
{
    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(Constant::dbPath);

    if (!db.open()) {
        throw "DB error";
    }

    return db;
}

QString UserService::hashPassword(const QString &password) const
{
    QByteArray hashBytes = QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Sha256);

    return QString(hashBytes);
}

void UserService::initDatabase()
{
    auto db = getDb();
    QSqlQuery query(
        "CREATE TABLE IF NOT EXISTS users ("
                "id integer PRIMARY KEY,"
                "login text NOT NULL,"
                "password text NOT NULL,"
                "table_constraint"
               ");"
    );

    if (!query.exec()) {
        throw "Fuck!";
    }

    QSqlQuery query2(
        "CREATE TABLE IF NOT EXISTS posts ("
                "id integer PRIMARY KEY,"
                "userId integer NOT NULL,"
                "date bigint NOT NULL,"
                "title text NOT NULL,"
                "body text NULL,"
                "post_order integer NOT NULL,"
                "table_constraint"
           ");"
    );

    if (!query.exec()) {
        throw "Fuck!";
    }

    db.close();
}
