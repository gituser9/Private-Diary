#include "postpresenter.h"

PostPresenter::PostPresenter(QObject *parent) : QObject (parent)
{

}

PostPresenter::~PostPresenter()
{

}

bool PostPresenter::createPost(const QString &title, const QString &text)
{
    if (title.isEmpty()) {
        emit showAlert(tr("Title is required"));
        return false;
    }
    return postService.createPost(title, text, appData->getUserId());
}

bool PostPresenter::updatePost(const QString &title, const QString &text, const int id)
{
    if (title.isEmpty()) {
        emit showAlert(tr("Title is required"));
        return false;
    }
    QString encryptedText = crypter.encrypt(text);
//    return postService.updatePost(title, text, id);
    return postService.updatePost(title, encryptedText, id);
}

bool PostPresenter::deletePost(const int id)
{
    if (id <= 0) {
        return false;
    }
    return postService.deletePost(id);
}

Post PostPresenter::getPost(const int id)
{
    if (id <= 0) {
        return Post();
    }
    Post post = postService.get(id);
    post.body = crypter.decrypt(post.body);

    return post;
}

QVector<Post> PostPresenter::getAll()
{
    return postService.getPosts(appData->getUserId());
}

void PostPresenter::setAppData(std::shared_ptr<AppData> appData)
{
    this->appData = appData;
    crypter.setAppData(appData);
}
