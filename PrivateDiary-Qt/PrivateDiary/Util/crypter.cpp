#include "crypter.h"
#include <QtDebug>

Crypter::Crypter()
{

}

QString Crypter::encrypt(const QString &toEncrypt) const
{
    if (toEncrypt.isNull() || toEncrypt.isEmpty()) {
        return "";
    }
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::ECB);
    QByteArray key = QCryptographicHash::hash(appData->getUserPassword().toUtf8(), QCryptographicHash::Sha256);

//    return QString(encryption.encode(bytes, key));
    return QString::fromUtf8(encryption.encode(toEncrypt.toUtf8(), key));
}

QString Crypter::decrypt(const QString &cipherString) const
{
    if (cipherString.isNull() || cipherString.isEmpty()) {
        return "";
    }
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::ECB);
    QByteArray key = QCryptographicHash::hash(appData->getUserPassword().toUtf8(), QCryptographicHash::Sha256);
    auto result = encryption.decode(cipherString.toUtf8(), key);

    qDebug() << cipherString;
    qDebug() << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    qDebug() << result;
    qDebug() << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    qDebug() << QString::fromUtf8(result);

    return QString(result);

}

void Crypter::setAppData(std::shared_ptr<AppData> appData)
{
    this->appData = appData;
}

