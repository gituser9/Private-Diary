#include "post.h"

QByteArray Post::toJson() const
{
    QJsonObject obj
    {
        { "id", id },
        { "title", title },
        { "body", body },
        { "date", date },
        { "order", order },
        { "userId", userId },
    };
    QJsonDocument doc(obj);

    return doc.toJson(QJsonDocument::JsonFormat::Compact);
}

Post Post::fromJson(const QJsonValue &json)
{
    Post post;
    post.id = json["id"].toInt();
    post.title = json["title"].toString("");
    post.body = json["body"].toString("");
    post.date = json["date"].toVariant().toLongLong();
    post.order = json["order"].toInt();
    post.userId = json["userId"].toInt();

    return post;
}
