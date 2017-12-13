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
    return postService.updatePost(title, text, id);
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
    return postService.get(id);
}

QVector<Post> PostPresenter::getAll()
{
    return postService.getPosts(appData->getUserId());
}

void PostPresenter::setAppData(std::shared_ptr<AppData> appData)
{
    this->appData = appData;
}
