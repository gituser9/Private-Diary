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
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setAppData(const int id, const QString &password);
    Q_INVOKABLE void create();
    Q_INVOKABLE void load(const int id);
    Q_INVOKABLE void remove(const int id);

private:

    std::shared_ptr<AppData> appData;
    QVector<Post> posts;
    PostPresenter presenter;

private slots:

    void setDataSlot(QVector<Post> newPosts);

};

#endif // POSTLISTMODEL_H
