#include "postservice.h"
#include <QDebug>


PostService::PostService()
{
    db = getDb();
    updatePrepare = QSqlQuery(db);

    if (!updatePrepare.prepare("update posts set title = :title, body = :body where id = :id")) {
        qDebug() << db.lastError().text();
        return;
    }
}

PostService::~PostService()
{
    db.close();
}

Post PostService::createPost(const QString &title, const QString &text, const int userId)
{
    if (!db.isOpen()) {
        db = getDb();
    }

    QSqlQuery query;
    query.prepare("insert into posts(userId, title, body, date, post_order) values(:userId, :title, :body, :date, 0)");
    query.bindValue(":userId", userId);
    query.bindValue(":title", crypter.encrypt(title));
    query.bindValue(":body", text);
    query.bindValue(":date", QDateTime::currentDateTime().toSecsSinceEpoch());

    if (!query.exec()) {
        return Post();
    }

    int insertedId = query.lastInsertId().toInt();
    query.prepare("update posts set post_order = :order where id = :id");
    query.bindValue(":order", insertedId);
    query.bindValue(":id", insertedId);

    if (!query.exec()) {
        return Post();
    }

    return get(insertedId);
}

bool PostService::updatePost(const QByteArray &title, const QByteArray &text, const int id)
{
    if (!db.isOpen()) {
        db = getDb();
    }

    updatePrepare.bindValue(":id", id);
    updatePrepare.bindValue(":title", title);
    updatePrepare.bindValue(":body", text);

    if (!updatePrepare.exec()) {
        qDebug() << db.lastError().text();
        return false;
    }

    return true;
}

bool PostService::updatePostPosition(const int postId, const int position)
{
    if (!db.isOpen()) {
        return false;
    }
    QSqlQuery query;
    query.prepare("update posts set post_order = :order where id = :id");
    query.bindValue(":order", position);
    query.bindValue(":id", postId);

    return query.exec();
}

bool PostService::deletePost(const int id)
{
    if (!db.isOpen()) {
        db = getDb();
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
        db = getDb();
    }

    QSqlQuery query;
    query.prepare("select id, title, date from posts where userId=? order by post_order");
    query.addBindValue(userId);

    if (query.size() > 0) {
        result.reserve(query.size());
    }
    if (!query.exec()) {
        return result;
    }
    while (query.next()) {
        Post post;
        post.title = crypter.decrypt(query.value(Constant::PostFields::title).toByteArray());
        post.date = query.value(Constant::PostFields::date).toLongLong();
        post.id = query.value(Constant::PostFields::id).toInt();
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
        qDebug() << db.lastError().text();
        return post;
    }

    query.next();
    post.id = id;
    post.title = crypter.decrypt(query.value(Constant::PostFields::title).toByteArray());
    post.body = crypter.decrypt(query.value(Constant::PostFields::body).toByteArray());

    return post;
}

void PostService::setCrypter(const Crypter &crypter)
{
    // TODO: must be on presenter only
    this->crypter = crypter;
}

QSqlDatabase PostService::getDb()
{
    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(Constant::dbPath);

    if (!db.open()) {
        throw "DB error";
    }

    return db;
}
