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

    QString encrypt(const QString &toEncrypt) const;
    QString decrypt(const QString &cipherString) const;

    void setAppData(std::shared_ptr<AppData> appData);

private:
    std::shared_ptr<AppData> appData;

    int getAlignedSize(int currSize, int alignment);



};

#endif // CRYPTER_H
