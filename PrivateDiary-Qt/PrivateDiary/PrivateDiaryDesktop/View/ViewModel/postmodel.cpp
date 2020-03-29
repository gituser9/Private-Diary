#include "postmodel.h"
#include <QtDebug>

PostModel::PostModel(QObject *parent) : QStringListModel(parent)
{

}

PostModel::PostModel(const QStringList &strings, QObject *parent) : QStringListModel(strings, parent)
{

}

/*int PostModel::rowCount(const QModelIndex &parent) const
{
    return _posts.size();
}*/

/*QVariant PostModel::data(const QModelIndex &index, int role) const
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
}*/

Qt::ItemFlags PostModel::flags(const QModelIndex &index) const
{

    Qt::ItemFlags defaultFlags = QStringListModel::flags(index);
        if (index.isValid()){
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
        }
        return defaultFlags;
}

void PostModel::resetData(const QVector<Post> &data)
{
    QStringList list;

    beginResetModel();
    _posts.clear();
    _posts = data;

    for (auto &&item : data) {
        list.append(item.title);
    }

    setStringList(list);
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

    QStringList list = stringList();
    list[index.row()] = title;

    setStringList(list);
    dataChanged(index, index);

}

Post PostModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        return _posts[index.row()];
    }
    return Post();
}
