#ifndef POSTPRESENTER_H
#define POSTPRESENTER_H

#include <QObject>
#include <QVector>

#include "Model/Service/postservice.h"
#include "Model/DataStructure/post.h"
#include "Model/DataStructure/appdata.h"
#include "Util/crypter.h"


class PostPresenter : public QObject
{
    Q_OBJECT
public:
    PostPresenter(QObject *parent = nullptr);
    ~PostPresenter();

    bool createPost(const QString &title, const QString &text);
    bool updatePost(const QString &title, const QString &text, const int id);
    bool deletePost(const int id);
    QVector<Post> getAll();
    Post getPost(const int id);
    void setAppData(std::shared_ptr<AppData> appData);

private:
    std::shared_ptr<AppData> appData;
    PostService postService;
    Crypter crypter;

signals:
    void showAlert(const QString &message);

public slots:
    void updatePostPosition(const int postId, const int position);

};

#endif // POSTPRESENTER_H
