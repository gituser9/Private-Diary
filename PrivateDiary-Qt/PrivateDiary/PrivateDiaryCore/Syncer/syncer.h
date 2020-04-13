#ifndef FIREBASESYNCER_H
#define FIREBASESYNCER_H

#include <memory>

#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include <QCryptographicHash>

#include "Model/DataStructure/constant.h"
#include "Model/DataStructure/appdata.h"
#include "Model/DataStructure/appsecret.h"


class Syncer : public QObject
{
    Q_OBJECT
public:
    enum NetworkAction {
        None,
        ReadAll,
        Read,
        Create,
        Update,
        Delete
    };

    explicit Syncer(QObject *parent = nullptr);
    void get(const QString &requestString, NetworkAction action);
    void remove(const QString &requestString);
    void post(const QString &address, const QByteArray &postData);
    void put(const QString &address, const QByteArray &postData);

    void setAppData(std::shared_ptr<AppData> appData);

private:
    QByteArray userSign;
    std::shared_ptr<AppData> appData;

    QNetworkAccessManager manager;
    NetworkAction currentAction;

    QNetworkRequest createRequest(const QString &url) const;

private slots:
    void slotFinished(QNetworkReply*reply);

signals:
    void readAllFinished(const QJsonArray &response);
    void readFinished(const QJsonObject &response);
    void createFinished(const QJsonObject &response);
    void updateFinished(const QJsonObject &response);
    void deleteFinished();

};

#endif // FIREBASESYNCER_H
