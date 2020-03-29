#ifndef POSTLISTMODEL_H
#define POSTLISTMODEL_H

#include <memory>

#include <QAbstractListModel>
#include <QVector>

#include "Model/DataStructure/post.h"
#include "Model/DataStructure/appdata.h"
#include "Presenter/postpresenter.h"


class PostListModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum TaskRoles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        BodyRole,
    };

    explicit PostListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
//    bool setData(const QModelIndex &index, const QVariant &value,
//                 int role = Qt::EditRole) override;

//    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
//    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
//    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setAppData(const int id, const QString &password);
    Q_INVOKABLE void create();
    Q_INVOKABLE void load(const int id);
    Q_INVOKABLE void remove(const int id);

private:
    std::shared_ptr<AppData> appData;
    QVector<Post> posts;
    PostPresenter presenter;

};

#endif // POSTLISTMODEL_H
