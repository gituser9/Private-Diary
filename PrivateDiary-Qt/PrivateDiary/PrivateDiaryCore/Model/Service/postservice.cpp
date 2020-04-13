#include "postservice.h"
#include <QDebug>


PostService::PostService()
{
    db = getDb();
    updatePrepare = QSqlQuery(db);
    updateTitlePrepare = QSqlQuery(db);

    if (!updatePrepare.prepare("update posts set title = :title, body = :body where id = :id")) {
        qDebug() << db.lastError().text();
        return;
    }
    if (!updateTitlePrepare.prepare("update posts set title = :title where id = :id")) {
        qDebug() << db.lastError().text();
        return;
    }

    syncerThread = new QThread(this);
    syncer = new Syncer(this);

    connect(syncer, &Syncer::readAllFinished, this, &PostService::getListSlot);
    connect(syncer, &Syncer::readFinished, this, &PostService::getSlot);

    syncer->moveToThread(syncerThread);
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

    Post post = get(insertedId);
    Post syncedPost = post;
    syncedPost.title = crypter.encrypt(title).toHex();
    syncer->post("posts", syncedPost.toJson());

    return post;
}

void PostService::upload(const int id)
{
    Post post = get(id);
    post.title = crypter.encrypt(post.title).toHex();
    post.body = crypter.encrypt(post.body).toHex();
    syncer->post("posts", post.toJson());
}

bool PostService::updatePost(const QByteArray &title, const QByteArray &text, const int id, bool withSyc)
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

    if (withSyc) {
        Post post = get(id);
        post.title = title.toHex();
        post.body = text.toHex();
        syncer->put(QString("posts/%1").arg(id), post.toJson());
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

bool PostService::updateTitlePost(const QString &title, const int id)
{
    if (!db.isOpen()) {
        db = getDb();
    }

    updateTitlePrepare.bindValue(":id", id);
    updateTitlePrepare.bindValue(":title", title);

    if (!updateTitlePrepare.exec()) {
        qDebug() << db.lastError().text();
        return false;
    }

    return true;
}

bool PostService::deletePost(const int id)
{
    if (!db.isOpen()) {
        db = getDb();
    }

    QSqlQuery query;
    query.prepare("delete from posts where id=?");
    query.addBindValue(id);

    syncer->remove(QString("posts/%1").arg(id));

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

    syncer->get("posts", Syncer::NetworkAction::ReadAll);
    return result;
}

Post PostService::get(const int id)
{
    Post post;
    QSqlQuery query;
    query.prepare("select title, body, userId, date from posts where id=?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << db.lastError().text();
        return post;
    }

    query.next();
    post.id = id;
    post.title = crypter.decrypt(query.value(Constant::PostFields::title).toByteArray());
    post.body = crypter.decrypt(query.value(Constant::PostFields::body).toByteArray());
    post.userId = query.value("userId").toInt();
    post.order = 0;
    post.date = query.value("date").toInt();

    syncer->get(QString("posts/%1").arg(id), Syncer::NetworkAction::Read);

    return post;
}

void PostService::setCrypter(const Crypter &crypter)
{
    // TODO: must be on presenter only
    this->crypter = crypter;
}

void PostService::setAppData(std::shared_ptr<AppData> appData)
{
    this->appData = appData;
    syncer->setAppData(appData);
}

void PostService::created(const QJsonObject &response)
{
    qDebug() << response;
}

void PostService::getListSlot(const QJsonArray &response)
{
    if (response.isEmpty()) {
        return;
    }

    QVector<Post> posts;
    posts.reserve(response.size());


    for (auto &&postJson : response) {
        const QByteArray titleData = postJson["title"].toVariant().toByteArray();

        Post post;
        post.id = postJson["id"].toInt();
        post.title = crypter.decrypt(QByteArray::fromHex(titleData));

        posts.append(post);
    }

    emit getListFromServer(posts);
}

void PostService::getSlot(const QJsonObject &response)
{
    const QByteArray titleData = response["title"].toVariant().toByteArray();
    const QByteArray bodyData = response["body"].toVariant().toByteArray();

    Post post;
    post.id = response["id"].toInt();
    post.title = crypter.decrypt(QByteArray::fromHex(titleData));
    post.body = crypter.decrypt(QByteArray::fromHex(bodyData));
    post.date = response["date"].toVariant().toLongLong();
    post.order = response["order"].toInt();
    post.userId = response["userId"].toInt();

    emit getFromServer(post);
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
