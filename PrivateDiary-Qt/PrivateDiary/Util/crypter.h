#ifndef CRYPTER_H
#define CRYPTER_H

#include <memory>
#include <QString>
#include <QCryptographicHash>


#include "qaesencryption.h"
#include "Model/DataStructure/appdata.h"


class Crypter
{
public:
    Crypter();
    ~Crypter();

    QByteArray encrypt(const QString &toEncrypt) const;
    QString decrypt(const QByteArray &cipherString) const;

    void setAppData(std::shared_ptr<AppData> appData);

private:
    std::shared_ptr<AppData> appData;
    QByteArray passwordHash;
    QAESEncryption *aesCrypter;

};

#endif // CRYPTER_H
