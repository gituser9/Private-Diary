#include "loginpage.h"

LoginPage::LoginPage(QObject *parent) : QObject (parent)
{
//    userPresenter.setView(this);

    userPresenter = new UserPresenter(this);
    connect(userPresenter, &UserPresenter::showMessage, this, &LoginPage::showAlert);
}

LoginPage::~LoginPage()
{

}

void LoginPage::showAlert(const QString &message)
{
    QMessageBox::warning(0, tr("Error"), message, QMessageBox::Ok);
}

bool LoginPage::registration(const QString &login, const QString &password) const
{
    if (!userPresenter->registration(login, password)) {
//        emit this->showAlert("Registration error");
        return false;
    }
    return true;
}

bool LoginPage::auth(const QString &login, const QString &password) const
{
    if (!userPresenter->auth(login, password)) {
        //ßshowAlert("Registration error");
        return false;
    }
    return true;
}

bool LoginPage::updateCredentioals(const QString &login, const QString &password) const
{
    return userPresenter->update(login, password);
}

void LoginPage::setAppData(std::shared_ptr<AppData> appData)
{
    this->appData = appData;
    userPresenter->setAppData(appData);
}
