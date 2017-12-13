#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QMessageBox>

#include "Model/DataStructure/appdata.h"
#include "Presenter/userpresenter.h"


class LoginPage : public QObject
{
    Q_OBJECT
public:
    LoginPage(QObject *parent = 0);
    ~LoginPage();

    //void showAlert(const QString &message) const;
    bool registration(const QString &login, const QString &password) const;
    bool auth(const QString &login, const QString &password) const;

    void setAppData(std::shared_ptr<AppData> appData);

public slots:
    void showAlert(const QString &message);

private:
    std::shared_ptr<AppData> appData;
    UserPresenter *userPresenter;

};

#endif // LOGINPAGE_H
