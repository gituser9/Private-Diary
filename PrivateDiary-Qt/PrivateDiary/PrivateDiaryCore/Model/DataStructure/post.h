#ifndef POST_H
#define POST_H

#include <QString>


class Post
{
public:
    QString title;
    QString body;
    long date;
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
};

#endif // POST_H
