#ifndef POST_H
#define POST_H

#include <QString>
//#include "constant.h"


class Post
{
public:
    int id;
    int userId;
    long date;
    QString title;
    QString body;

    Post() {
       id = 0;
       userId = 0;
       date = 0;
       title = "";
       body = "";
    }
};

#endif // POST_H
