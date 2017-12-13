#ifndef POSTSERVICE_H
#define POSTSERVICE_H

#include <memory>
#include <QtSql>
#include <QDir>
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
    bool updatePost(const QString &title, const QString &text, const int id);
    bool deletePost(const int id);

    QVector<Post> getPosts(const int userId);
    Post get(const int id);

private:
    QSqlDatabase db;


};

#endif // POSTSERVICE_H
