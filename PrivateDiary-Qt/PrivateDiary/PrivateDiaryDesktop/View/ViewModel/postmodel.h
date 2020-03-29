#ifndef POSTMODEL_H
#define POSTMODEL_H

#include <memory>
#include <QObject>
#include <QAbstractListModel>
#include <QDateTime>
#include <QStringListModel>
#include <QMimeData>
#include <QDataStream>

#include "Model/DataStructure/post.h"


class PostModel : public QStringListModel
{

    Q_OBJECT
public:
    explicit PostModel(QObject *parent = nullptr);
    explicit PostModel(const QStringList & strings, QObject *parent = nullptr);

//    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void resetData(const QVector<Post> &data);
    void updateTitle(const int id, const QString &title, const QModelIndex &index);
    Post getItem(const QModelIndex &index) const;


private:
    QVector<Post> _posts;

signals:
    void dragged(const int postId, const int position);
};

#endif // POSTMODEL_H
