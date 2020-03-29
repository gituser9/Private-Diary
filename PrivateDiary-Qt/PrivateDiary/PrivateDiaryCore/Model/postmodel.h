#ifndef POSTMODEL_H
#define POSTPOSTMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "DataStructure/post.h"


class PostModel : public QAbstractListModel
{

    Q_OBJECT
public:
    explicit PostModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void resetData(const QVector<Post> &data);
    Post getItem(const QModelIndex &index) const;

private:
    QVector<Post> _posts;
};

#endif // POSTMODEL_H
