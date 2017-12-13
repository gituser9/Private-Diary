#include "userpresenter.h"


UserPresenter::UserPresenter(QObject *parent) : QObject (parent)
{

}

UserPresenter::~UserPresenter()
{

}

bool UserPresenter::registration(const QString &login, const QString &password)
{
    if (login.isEmpty() || password.isEmpty()) {
        emit showMessage(tr("Login and password is required"));
        return false;
    }
    if (!userService.registration(login, password)) {
        emit showMessage(tr("Registration Error"));
        return false;
    }
    return auth(login, password);
}

bool UserPresenter::auth(const QString &login, const QString &password)
{
    if (login.isEmpty() || password.isEmpty()) {
        emit showMessage(tr("Login and password is required"));
        return false;
    }
    if (!userService.auth(login, password)) {
        emit showMessage(tr("Auth Error"));
        return false;
    }
    return true;
}

void UserPresenter::setAppData(std::shared_ptr<AppData> appData)
{
    this->appData = appData;
    userService.setAppData(appData);
}
