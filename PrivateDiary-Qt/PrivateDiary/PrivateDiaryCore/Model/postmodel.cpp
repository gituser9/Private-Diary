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

    switch (role) {
    case Qt::DisplayRole:
        return post.title;
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

Post PostModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        return _posts[index.row()];
    }
    return Post();
}
