#include "userpresenter.h"


UserPresenter::UserPresenter(QObject *parent) : QObject (parent)
{

}

UserPresenter::~UserPresenter()
{

}

int UserPresenter::registration(const QString &login, const QString &password)
{
    if (appData == nullptr) {
        appData = std::make_shared<AppData>();
        userService.setAppData(appData);
    }
    if (login.isEmpty() || password.isEmpty()) {
        emit showMessage(tr("Login and password is required"));
        return false;
    }

    int id = userService.registration(login, password);

    if (id == 0) {
        emit showMessage(tr("Registration Error"));
        return false;
    }

    return id;
}

int UserPresenter::auth(const QString &login, const QString &password)
{
    if (appData == nullptr) {
        appData = std::make_shared<AppData>();
        userService.setAppData(appData);
    }
    if (login.isEmpty() || password.isEmpty()) {
        emit showMessage(tr("Login and password is required"));
        return false;
    }

    int id = userService.auth(login, password);

    if (id == 0) {
        emit showMessage(tr("Auth Error"));
        return false;
    }

    return id;
}

bool UserPresenter::update(const QString &login, const QString &password)
{
    if (login.isEmpty() || password.isEmpty()) {
        emit showMessage(tr("Login and password is required"));
        return false;
    }
    if (!userService.update(login, password)) {
        emit showMessage(tr("Update Error"));
        return false;
    }
    return true;
}

void UserPresenter::setAppData(std::shared_ptr<AppData> appData)
{
    this->appData = appData;
    userService.setAppData(appData);
}
