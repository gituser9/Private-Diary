#ifndef POSTMODEL_H
#define POSTPOSTMODEL_H

#include <memory>
#include <QObject>
#include <QAbstractListModel>
#include <QDateTime>

#include "Model/DataStructure/post.h"


class PostModel : public QAbstractListModel
{

    Q_OBJECT
public:
    explicit PostModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void resetData(const QVector<Post> &data);
    void updateTitle(const int id, const QString &title, const QModelIndex &index);
    Post getItem(const QModelIndex &index) const;

private:
    QVector<Post> _posts;
};

#endif // POSTMODEL_H
