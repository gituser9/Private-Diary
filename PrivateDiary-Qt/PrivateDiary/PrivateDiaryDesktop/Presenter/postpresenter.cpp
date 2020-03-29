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
    QByteArray encryptedText = crypter.encrypt(text);
    QByteArray encryptedTitle = crypter.encrypt(title);
    return postService.updatePost(encryptedTitle, encryptedText, id);
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

    // TODO: decryption must be here
    Post post = postService.get(id);

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
    postService.setCrypter(crypter);
}

void PostPresenter::updatePostPosition(const int postId, const int position)
{
    if (postId <= 0 || position < 0) {
        return;
    }
    if (!postService.updatePostPosition(postId, position)) {
        emit showAlert(tr("Reorder error"));
    }
}