#include "credentialdialog.h"
#include "ui_credentialdialog.h"

CredentialDialog::CredentialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CredentialDialog)
{
    ui->setupUi(this);



}

CredentialDialog::~CredentialDialog()
{
    delete ui;
}

QString CredentialDialog::getLogin() const
{
    return ui->leLogin->text();
}

QString CredentialDialog::getPassword() const
{
    return ui->lePassword->text();
}
