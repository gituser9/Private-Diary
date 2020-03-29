#ifndef POSTPRESENTER_H
#define POSTPRESENTER_H

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
    Q_INVOKABLE bool updatePost(const QString &title, const QString &text, const int id);
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

signals:
    void showAlert(const QString &message);

public slots:
    void updatePostPosition(const int postId, const int position);

};

#endif // POSTPRESENTER_H
