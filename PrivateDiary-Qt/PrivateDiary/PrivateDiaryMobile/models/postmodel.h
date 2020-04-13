#ifndef POSTMODEL_H
#define POSTMODEL_H

#include <memory>

#include <QAbstractItemModel>

#include "Model/DataStructure/post.h"
#include "Model/DataStructure/appdata.h"
#include "Presenter/postpresenter.h"


class PostModel : public QAbstractItemModel
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)

public:
    explicit PostModel(QObject *parent = nullptr);

    // Basic functionality:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    Q_INVOKABLE void setAppData(const int id, const QString &password);
    Q_INVOKABLE void load(const int id);
    Q_INVOKABLE void updatePost(const int id, const QString &title, const QString &body, bool withSync);

    QString title() const;
    QString body() const;

public slots:
    void setTitle(QString title);
    void setBody(QString body);
    void setDataSlot(Post newPost);

signals:
    void titleChanged(QString title);
    void bodyChanged(QString body);

private:
    Post post;
    std::shared_ptr<AppData> appData;
    PostPresenter presenter;

    QString m_title;
    QString m_body;
};

#endif // POSTMODEL_H
