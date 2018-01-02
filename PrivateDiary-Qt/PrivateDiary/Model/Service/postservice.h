#ifndef POSTSERVICE_H
#define POSTSERVICE_H

#include <memory>
#include <QtSql>
#include <QDateTime>
#include <QVector>

#include "Util/crypter.h"
#include "Model/DataStructure/constant.h"
#include "Model/DataStructure/post.h"


class PostService
{
public:
    PostService();
    ~PostService();

    bool createPost(const QString &title, const QString &text, const int userId);
    bool updatePost(const QByteArray &title, const QByteArray &text, const int id);
    bool updatePostPosition(const int postId, const int position);
    bool deletePost(const int id);

    QVector<Post> getPosts(const int userId);
    Post get(const int id);

    void setCrypter(const Crypter &crypter);

private:
    QSqlDatabase db;
    Crypter crypter;


};

#endif // POSTSERVICE_H
