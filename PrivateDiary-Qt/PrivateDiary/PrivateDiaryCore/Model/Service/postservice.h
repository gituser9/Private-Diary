#ifndef POSTSERVICE_H
#define POSTSERVICE_H

#include <memory>

#include <QtSql>
#include <QDateTime>
#include <QVector>
#include <QThread>
#include <QJsonObject>
#include <QJsonArray>

#include "Util/crypter.h"
#include "Model/DataStructure/constant.h"
#include "Model/DataStructure/post.h"
#include "Model/DataStructure/appdata.h"
#include "Syncer/syncer.h"


class PostService : public QObject
{
    Q_OBJECT
public:
    PostService();
    ~PostService();

    Post createPost(const QString &title, const QString &text, const int userId);
    void upload(const int id);
    bool updatePost(const QByteArray &title, const QByteArray &text, const int id, bool withSyc);
    bool updatePostPosition(const int postId, const int position);
    bool updateTitlePost(const QString &title, const int id);
    bool deletePost(const int id);

    QVector<Post> getPosts(const int userId);
    Post get(const int id);

    void setCrypter(const Crypter &crypter);
    void setAppData(std::shared_ptr<AppData> appData);

public slots:
    void created(const QJsonObject &response);
    void getListSlot(const QJsonArray &response);
    void getSlot(const QJsonObject &response);

signals:
    void getListFromServer(QVector<Post> posts);
    void getFromServer(Post post);

private:
    QSqlDatabase db;
    Crypter crypter;
    Syncer *syncer;
    QThread *syncerThread;
    std::shared_ptr<AppData> appData;


    QSqlDatabase getDb();
    QSqlQuery updatePrepare;
    QSqlQuery updateTitlePrepare;
};

#endif // POSTSERVICE_H
