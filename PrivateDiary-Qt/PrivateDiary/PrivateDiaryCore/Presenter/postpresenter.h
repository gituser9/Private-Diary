#ifndef POSTPRESENTER_H
#define POSTPRESENTER_H

#include <algorithm>

#include <QObject>
#include <QVector>
#include <QThread>

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

    Q_INVOKABLE Post createPost(const QString &title, const QString &text);
    Q_INVOKABLE bool updatePost(const QString &title, const QString &text, const int id, bool withSync);
    Q_INVOKABLE bool deletePost(const int id);
    Q_INVOKABLE QVector<Post> getAll();
    Q_INVOKABLE Post getPost(const int id);
    Q_INVOKABLE void setAppData(const int id, const QString &password);
    void setAppData(std::shared_ptr<AppData> appData);

private:
    std::shared_ptr<AppData> appData;
    PostService postService;
    Crypter crypter;
    QThread *serviceThread;
    QVector<Post> posts;

signals:
    void showAlert(const QString &message);
    void setPosts(QVector<Post> newPosts);
    void setPost(Post newPosts);

public slots:
    void updatePostPosition(const int postId, const int position);
    void setPostsSlot(QVector<Post> newPosts);
    void setPostSlot(Post newPost);

};

#endif // POSTPRESENTER_H
