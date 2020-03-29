#include "crypter.h"


Crypter::Crypter()
{
//    aesCrypter = new QAESEncryption(QAESEncryption::AES_128, QAESEncryption::ECB);
    aesCrypter = std::make_shared<QAESEncryption>(QAESEncryption::AES_128, QAESEncryption::ECB);
}

Crypter::~Crypter()
{
//    if (aesCrypter != nullptr) {
//        delete aesCrypter;
//    }
}

QByteArray Crypter::encrypt(const QString &toEncrypt) const
{
    if (toEncrypt.isNull() || toEncrypt.isEmpty()) {
        return "";
    }


    return aesCrypter->encode(toEncrypt.toUtf8(), passwordHash);
}

QString Crypter::decrypt(const QByteArray &cipherString) const
{
    if (cipherString.isNull() || cipherString.isEmpty()) {
        return "";
    }

    auto dec = aesCrypter->decode(cipherString, passwordHash);

    return QString::fromUtf8(dec.data());
}

void Crypter::setAppData(std::shared_ptr<AppData> appData)
{
    this->appData = appData;

    passwordHash = QCryptographicHash::hash(appData->getUserPassword().toUtf8(), QCryptographicHash::Md5);
}

