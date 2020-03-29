#include "postmodel.h"

PostModel::PostModel(QObject *parent) : QAbstractItemModel(parent)
{
    appData = std::make_shared<AppData>();
}

QModelIndex PostModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex PostModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int PostModel::rowCount(const QModelIndex &parent) const
{
    return 1;
}

int PostModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant PostModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

bool PostModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags PostModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

void PostModel::setAppData(const int id, const QString &password)
{
    appData->setUserId(id);
    appData->setUserPassword(password);

    presenter.setAppData(appData);
//    posts = presenter.getAll();

//    beginResetModel();
    //    endResetModel();
}

void PostModel::load(const int id)
{
    post = presenter.getPost(id);
    setBody(post.body);
    setTitle(post.title);
}

void PostModel::updatePost(const int id, const QString &title, const QString &body)
{
    presenter.updatePost(title, body, id);
}

QString PostModel::title() const
{
    return m_title;
}

QString PostModel::body() const
{
    return m_body;
}

void PostModel::setTitle(QString title)
{
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged(m_title);
}

void PostModel::setBody(QString body)
{
    if (m_body == body)
        return;

    m_body = body;
    emit bodyChanged(m_body);
}
