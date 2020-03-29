#ifndef USERPRESENTER_H
#define USERPRESENTER_H

#include <memory>
#include <QObject>
#include <QString>

#include "Model/Service/userservice.h"
#include "Model/DataStructure/appdata.h"


class UserPresenter : public QObject
{
    Q_OBJECT
public:
    UserPresenter(QObject *parent = nullptr);
    ~UserPresenter();

    Q_INVOKABLE int registration(const QString &login, const QString &password);
    Q_INVOKABLE int auth(const QString &login, const QString &password);
    bool update(const QString &login, const QString &password);

    void setAppData(std::shared_ptr<AppData> appData);

private:
    std::shared_ptr<AppData> appData;
    UserService userService;

signals:
    void showMessage(const QString &message);

};

#endif // USERPRESENTER_H
