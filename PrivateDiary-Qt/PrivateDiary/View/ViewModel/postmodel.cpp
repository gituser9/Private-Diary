#include "postmodel.h"

PostModel::PostModel(QObject *parent) : QAbstractListModel(parent)
{

}

int PostModel::rowCount(const QModelIndex &parent) const
{
    return _posts.size();
}

QVariant PostModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    Post post = _posts[index.row()];
    QDateTime dateTime;
    dateTime.setTime_t(post.date);

    // TODO: delegate
    switch (role) {
    case Qt::DisplayRole:
        return post.title + "\n" + dateTime.toString(Qt::SystemLocaleShortDate);
    default:
        return QVariant();
    }
}

void PostModel::resetData(const QVector<Post> &data)
{
    beginResetModel();
    _posts.clear();
    _posts = data;
    endResetModel();
}

void PostModel::updateTitle(const int id, const QString &title, const QModelIndex &index)
{
    // TODO: <algorithm>
    for (auto &&post : _posts) {
        if (post.id == id) {
            post.title = title;
            break;
        }
    }
    dataChanged(index, index);

}

Post PostModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        return _posts[index.row()];
    }
    return Post();
}
