#include "postlistmodel.h"

PostListModel::PostListModel(QObject *parent) : QAbstractListModel(parent)
{
    appData = std::make_shared<AppData>();

    connect(&presenter, &PostPresenter::setPosts, this, &PostListModel::setDataSlot);
}


int PostListModel::rowCount(const QModelIndex &) const
{
    return posts.size();
}

QVariant PostListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    Post post = posts[index.row()];

    switch (role) {
    case Qt::DisplayRole:
        return {};
    case IdRole:
        return QVariant::fromValue(post.id);
    case TitleRole:
        return QVariant::fromValue(post.title);
    case BodyRole:
        return QVariant::fromValue(post.body);
    default:
        return {};
    }
}

QHash<int, QByteArray> PostListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[TitleRole] = "title";
    roles[BodyRole] = "body";

    return roles;
}

void PostListModel::setAppData(const int id, const QString &password)
{
    appData->setUserId(id);
    appData->setUserPassword(password);

    presenter.setAppData(appData);
    posts = presenter.getAll();

    beginResetModel();
    endResetModel();
}

void PostListModel::create()
{
    Post post = presenter.createPost("New Post", "");

    if (post.id == 0) {
        return;
    }

    beginResetModel();
    posts.append(post);
    endResetModel();
}

void PostListModel::load(const int id)
{
    Post post = presenter.getPost(id);

    for (Post &item : posts) {
        if (item.id == id) {
            item.body = post.body;
            return;
        }
    }
}

void PostListModel::remove(const int id)
{
    presenter.deletePost(id);
    int index = -1;

    for (int i = 0; i < posts.size(); ++i) {
        if (posts[i].id == id) {
            index = i;
            break;
        }
    }
    if (index < 0) {
        return;
    }

    this->beginResetModel();
    posts.removeAt(index);
    this->endResetModel();
}

void PostListModel::setDataSlot(QVector<Post> newPosts)
{
    this->beginResetModel();
    posts = newPosts;
    this->endResetModel();
}

