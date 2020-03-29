#include "postlistmodel.h"

PostListModel::PostListModel(QObject *parent) : QAbstractListModel(parent)
{
    appData = std::make_shared<AppData>();
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

//bool PostListModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (data(index, role) != value) {
//        // FIXME: Implement me!
//        emit dataChanged(index, index, QVector<int>() << role);
//        return true;
//    }
//    return false;
//}

//Qt::ItemFlags PostListModel::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return Qt::NoItemFlags;

//    return Qt::ItemIsEditable; // FIXME: Implement me!
//}

//bool PostListModel::insertRows(int row, int count, const QModelIndex &parent)
//{
//    beginInsertRows(parent, row, row + count - 1);
//    posts.append(post);
//    endInsertRows();

//    return true;
//}

//bool PostListModel::removeRows(int row, int count, const QModelIndex &parent)
//{
//    beginRemoveRows(parent, row, row + count - 1);
//    posts.removeAt(row);
//    endRemoveRows();

//    return true;
//}

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

