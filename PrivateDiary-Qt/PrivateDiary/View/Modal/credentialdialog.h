#ifndef CREDENTIALDIALOG_H
#define CREDENTIALDIALOG_H

#include <QDialog>

namespace Ui {
class CredentialDialog;
}

class CredentialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CredentialDialog(QWidget *parent = 0);
    ~CredentialDialog();

    QString getLogin() const;
    QString getPassword() const;

private:
    Ui::CredentialDialog *ui;
};

#endif // CREDENTIALDIALOG_H
