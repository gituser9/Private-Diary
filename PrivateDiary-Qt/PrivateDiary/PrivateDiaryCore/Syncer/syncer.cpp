#include "syncer.h"

Syncer::Syncer(QObject *parent) : QObject (parent)
{
    connect(&manager, &QNetworkAccessManager::finished, this, &Syncer::slotFinished);

    currentAction = None;
}

void Syncer::get(const QString &requestString, NetworkAction action)
{
    currentAction = action;

    QNetworkRequest request = createRequest(requestString);
    manager.get(request);
}

void Syncer::remove(const QString &requestString)
{
    currentAction = Delete;
    QNetworkRequest request = createRequest(requestString);
    manager.deleteResource(request);
}

void Syncer::post(const QString &address, const QByteArray &postData)
{
    currentAction = Create;
    QNetworkRequest request = createRequest(address);
    manager.post(request, postData);
}

void Syncer::put(const QString &address, const QByteArray &postData)
{
    currentAction = Update;
    QNetworkRequest request = createRequest(address);
    manager.put(request, postData);
}

void Syncer::setAppData(std::shared_ptr<AppData> appData)
{
    this->appData = appData;
    userSign = QCryptographicHash::hash(appData->getUserPassword().toUtf8(), QCryptographicHash::Sha512).toHex();
}

QNetworkRequest Syncer::createRequest(const QString &url) const
{
    QJsonDocument claims = Constant::token.getPayloadJDoc();
    uint now = QDateTime::currentDateTime().toTime_t();

    if (now >= claims["exp"].toVariant().toLongLong()) {
        qint64 days = QDateTime::currentDateTime().addDays(Constant::tokenLifetime).toTime_t();
        QJsonWebToken jwt;
        jwt.appendClaim("id", QJsonValue(claims["exp"].toVariant().toLongLong()));
        jwt.appendClaim("sign", QJsonValue(QString(userSign)));
        jwt.appendClaim("exp", QJsonValue(days));
        jwt.setSecret(AppSecret::jwtSign);

        Constant::jwt = jwt.getToken();
        Constant::token = jwt;
    }

    const QUrl uri(Constant::fbHost + url);
    QNetworkRequest request(uri);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer " + Constant::jwt).toUtf8());

    return request;
}

void Syncer::slotFinished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    reply->deleteLater();

    if (statusCode != 200 && statusCode != 201) {
        return;
    }

    const QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    const QJsonObject obj = jsonDoc.object();

    switch (currentAction) {
    case NetworkAction::ReadAll:
        emit readAllFinished(jsonDoc.array());
        break;
    case NetworkAction::Read:
        emit readFinished(obj);
        break;
    case NetworkAction::Create:
        emit createFinished(obj);
        break;
    case NetworkAction::Update:
        emit updateFinished(obj);
        break;
    case NetworkAction::Delete:
        emit deleteFinished();
        break;
    case NetworkAction::None:
        break;
    }

    currentAction = NetworkAction::None;
}
