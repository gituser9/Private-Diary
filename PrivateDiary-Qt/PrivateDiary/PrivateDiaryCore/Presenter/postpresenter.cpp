#include "postpresenter.h"

PostPresenter::PostPresenter(QObject *parent) : QObject (parent)
{
    serviceThread = new QThread(this);
//    postService.move

    connect(&postService, &PostService::getListFromServer, this, &PostPresenter::setPostsSlot);
    connect(&postService, &PostService::getFromServer, this, &PostPresenter::setPostSlot);
}

PostPresenter::~PostPresenter()
{

}

Post PostPresenter::createPost(const QString &title, const QString &text)
{
    if (title.isEmpty()) {
        emit showAlert(tr("Title is required"));
        return Post();
    }

    Post post = postService.createPost(title, text, appData->getUserId());

    if (post.id == 0) {
        emit showAlert(tr("Create new post error"));
        return Post();
    }

    return post;
}

bool PostPresenter::updatePost(const QString &title, const QString &text, const int id, bool withSync)
{
    if (title.isEmpty()) {
        emit showAlert(tr("Title is required"));
        return false;
    }
    QByteArray encryptedText = crypter.encrypt(text);
    QByteArray encryptedTitle = crypter.encrypt(title);
    return postService.updatePost(encryptedTitle, encryptedText, id, withSync);
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

void PostPresenter::setAppData(const int id, const QString &password)
{
    appData = std::make_shared<AppData>();
    appData->setUserId(id);
    appData->setUserPassword(password);

    crypter.setAppData(appData);
    postService.setCrypter(crypter);
}

QVector<Post> PostPresenter::getAll()
{
    posts = postService.getPosts(appData->getUserId());
    return posts;
}

void PostPresenter::setAppData(std::shared_ptr<AppData> appData)
{
    this->appData = appData;
    crypter.setAppData(appData);
    postService.setAppData(appData);
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

void PostPresenter::setPostsSlot(QVector<Post> newPosts)
{
    QVector<Post>::const_iterator begin = newPosts.begin();
    QVector<Post>::const_iterator end = newPosts.end();

    // update existig posts
    for (Post &post : posts) {
        auto findedPostIt = std::find_if(begin, end, [&](auto p) {
            return p.id == post.id;
        });
        if (findedPostIt != end && post.title != findedPostIt->title) {
            post.title = findedPostIt->title;
            postService.updateTitlePost(post.title, post.id);
        } else  {
            // upload
            postService.upload(post.id);
        }
    }

    // add new posts
    begin = posts.begin();
    end = posts.end();

    for (Post &post : newPosts) {
        auto findedPostIt = std::find_if(begin, end, [&](auto p) {
            return p.id == post.id;
        });
        if (findedPostIt == end) {
            posts.append(*findedPostIt);
        }
    }

    emit setPosts(posts);
}

void PostPresenter::setPostSlot(Post newPost)
{
    emit setPost(newPost);
}
