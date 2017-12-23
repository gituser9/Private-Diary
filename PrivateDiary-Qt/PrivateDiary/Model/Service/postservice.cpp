#include "postservice.h"


PostService::PostService()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(Constant::dbPath);

    if (!db.open()) {
        throw "DB error";
    }
}

PostService::~PostService()
{
    db.close();
}

bool PostService::createPost(const QString &title, const QString &text, const int userId)
{
    if (!db.isOpen()) {
        return false;
    }

    QSqlQuery query;
    query.prepare("insert into posts(userId, title, body, date) values(:userId, :title, :body, :date)");
    query.bindValue(":userId", userId);
    query.bindValue(":title", crypter.encrypt(title));
    query.bindValue(":body", text);
    query.bindValue(":date", QDateTime::currentDateTime().toSecsSinceEpoch());

    return query.exec();
}

bool PostService::updatePost(const QByteArray &title, const QByteArray &text, const int id)
{
    if (!db.isOpen()) {
        return false;
    }

    QSqlQuery query;
    query.prepare("update posts set title=:title, body=:body where id=:id");
    query.bindValue(":id", id);
    query.bindValue(":title", title);
    query.bindValue(":body", text);

    return query.exec();
}

bool PostService::deletePost(const int id)
{
    if (!db.isOpen()) {
        return false;
    }

    QSqlQuery query;
    query.prepare("delete from posts where id=?");
    query.addBindValue(id);

    return query.exec();
}

QVector<Post> PostService::getPosts(const int userId)
{
    QVector<Post> result;

    if (!db.isOpen()) {
        return result;
    }

    QSqlQuery query;
    query.prepare("select id, title, date from posts where userId=?");
    query.addBindValue(userId);

    if (!query.exec()) {
        return result;
    }
    while (query.next()) {
        Post post;
        post.title = crypter.decrypt(query.value("title").toByteArray());
        post.date = query.value("date").toLongLong();
        post.id = query.value("id").toInt();
        result.append(post);
    }

    return result;
}

Post PostService::get(const int id)
{
    Post post;
    QSqlQuery query;
    query.prepare("select title, body from posts where id=?");
    query.addBindValue(id);

    if (!query.exec()) {
        return post;
    }

    query.next();
    post.title = crypter.decrypt(query.value("title").toByteArray());
    post.body = crypter.decrypt(query.value("body").toByteArray());

    return post;
}

void PostService::setCrypter(const Crypter &crypter)
{
    // TODO: must be on presenter only
    this->crypter = crypter;
}
