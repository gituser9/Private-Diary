#include "userservice.h"


UserService::UserService()
{
    initDatabase();
}

int UserService::registration(const QString &login, const QString &password)
{
    auto db = getDb();
    QSqlQuery query;
    query.prepare("select count(*) from users where login=?");
    query.addBindValue(login);

    if (!query.exec()) {
        db.close();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();

    if (count != 0) {
        db.close();
        return false;
    }

    QString hashedPassword = hashPassword(password);
    query.prepare("insert into users(login, password) values(?, ?)");
    query.addBindValue(login);
    query.addBindValue(hashedPassword);

    if (!query.exec()) {
        db.close();
        return 0;
    }

    query.prepare("select id from users where login=? and password=?");
    query.addBindValue(login);
    query.addBindValue(hashedPassword);
    query.exec();
    query.next();
    appData->setUserId(query.value(Constant::UserFields::id).toInt());

    db.close();

    return auth(login, password);
}

int UserService::auth(const QString &login, const QString &password)
{
    auto db = getDb();
    QString hashedPassword = hashPassword(password);
    QSqlQuery query;
    query.prepare("select id from users where login=? and password=?");
    query.addBindValue(login);
    query.addBindValue(hashedPassword);

    if (!query.exec()) {
        db.close();
        return false;
    }

    query.next();
    int id = query.value(Constant::UserFields::id).toInt();
    appData->setUserId(id);

    db.close();
    return id;
}

bool UserService::update(const QString &login, const QString &password)
{
    auto db = getDb();
    QString hashedPassword = hashPassword(password);
    QSqlQuery query;
    query.prepare("select login, password from users where id=?");
    query.addBindValue(appData->getUserId());

    if (!query.exec()) {
        db.close();
        return false;
    }

    query.next();
    QString currentLogin = query.value(Constant::UserFields::login).toString();
    QString currentPassword = query.value(Constant::UserFields::password).toString();

    if (login != currentLogin) {
        query.prepare("update users set login=? where id=?");
        query.addBindValue(login);
        query.addBindValue(appData->getUserId());

        if (!query.exec()) {
            db.close();
            return false;
        }
    }
    if (hashedPassword != currentPassword) {
        if (!recryptedPosts(password)) {
            db.close();
            return false;
        }

        query.prepare("update users set password=? where id=?");
        query.addBindValue(hashedPassword);
        query.addBindValue(appData->getUserId());

        if (!query.exec()) {
            db.close();
            return false;
        }
    }
    db.close();
    return true;
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

bool UserService::recryptedPosts(const QString &newPassword)
{
    // decrypt with old password
    crypter.setAppData(appData);
    QVector<Post> result;
    QSqlQuery query;
    query.prepare("select id, title, body from posts where userId=?");
    query.addBindValue(appData->getUserId());

    if (query.size() > 0) {
        result.reserve(query.size());
    }
    if (!query.exec()) {
        return false;
    }
    while (query.next()) {
        Post post;
        post.title = crypter.decrypt(query.value(Constant::PostFields::title).toByteArray());
        post.id = query.value(Constant::PostFields::id).toInt();
        post.body = crypter.decrypt(query.value(Constant::PostFields::body).toByteArray());
        result.append(post);
    }

    // encrypr with new password
    appData->setUserPassword(newPassword);
    crypter.setAppData(appData);

    for (auto &&item : result) {
        QByteArray encryptedText = crypter.encrypt(item.body);
        QByteArray encryptedTitle = crypter.encrypt(item.title);
        query.prepare("update posts set title=:title, body=:body where id=:id");
        query.bindValue(":id", item.id);
        query.bindValue(":title", encryptedTitle);
        query.bindValue(":body", encryptedText);

        if (!query.exec()) {
            return false;
        }
    }

    return true;
}
