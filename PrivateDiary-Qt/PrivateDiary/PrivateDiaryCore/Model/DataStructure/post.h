#ifndef POST_H
#define POST_H

#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>


class Post
{
public:
    QString title;
    QString body;
    qint64 date;
    int id;
    int userId;
    int order;


    Post() {
       id = 0;
       userId = 0;
       date = 0;
       title = "";
       body = "";
    }

    Post(const QString &&newTitle) {
       id = 0;
       userId = 0;
       date = 0;
       title = newTitle;
       body = "";
    }

    QByteArray toJson() const;
    static Post fromJson(const QJsonValue &json);
};

#endif // POST_H
