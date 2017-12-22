#include "crypter.h"
#include "aes.h"
#include <QtDebug>

Crypter::Crypter()
{

}

QString Crypter::encrypt(const QString &toEncrypt)
{
    if (toEncrypt.isNull() || toEncrypt.isEmpty()) {
        return "";
    }
    /*QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::ECB);
    QByteArray key = QCryptographicHash::hash(appData->getUserPassword().toUtf8(), QCryptographicHash::Sha256);

    return QString::fromUtf8(encryption.encode(toEncrypt.toUtf8(), key));*/

    /*uint8_t* key = (uint8_t*) QCryptographicHash::hash(appData->getUserPassword().toUtf8(), QCryptographicHash::Md5).constData();
    uint8_t* input = (uint8_t*) toEncrypt.toStdString().c_str();
    uint8_t* output;*/

    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(appData->getUserPassword().toUtf8());
    QByteArray keyData = hash.result();

    const ushort *rawData = toEncrypt.utf16();
    void *rawDataVoid = (void*)rawData;
    const char *rawDataChar = static_cast<char*>(rawDataVoid);
    QByteArray inputData;
    // ushort is 2*uint8_t + 1 byte for '\0'
    inputData.append(rawDataChar, toEncrypt.size() * 2 + 1);

    const int length = inputData.size();
    int encryptionLength = getAlignedSize(length, 16);

    QByteArray encodingBuffer(encryptionLength, 0);
    inputData.resize(encryptionLength);

//    AES_ECB_encrypt(input, key, output, sizeof(input));
    AES_ECB_encrypt((uint8_t*)inputData.data(), (const uint8_t*)keyData.data(), (uint8_t*)encodingBuffer.data(), encryptionLength);

    //return QString(encodingBuffer);
    QByteArray data(encodingBuffer.data(), encryptionLength);
    QString hex = QString::fromLatin1(data.toHex());
    return hex;
}

QString Crypter::decrypt(const QString &cipherString) const
{
    if (cipherString.isNull() || cipherString.isEmpty()) {
        return "";
    }
    /*QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::ECB);
    QByteArray key = QCryptographicHash::hash(appData->getUserPassword().toUtf8(), QCryptographicHash::Sha256);
    auto result = encryption.decode(cipherString.toUtf8(), key);

    qDebug() << cipherString;
    qDebug() << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    qDebug() << result;
    qDebug() << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    qDebug() << QString::fromUtf8(result);

    return QString(result);*/
    uint8_t* key = (uint8_t*) QCryptographicHash::hash(appData->getUserPassword().toUtf8(), QCryptographicHash::Md5).constData();
    uint8_t* input = (uint8_t*) cipherString.toStdString().c_str();
    uint8_t* output;

    AES_ECB_decrypt(input, key, output, sizeof(input));

    QString((char*)output);
}

void Crypter::setAppData(std::shared_ptr<AppData> appData)
{
    this->appData = appData;
}

int Crypter::getAlignedSize(int currSize, int alignment)
{
    int padding = (alignment - currSize % alignment) % alignment;
            return currSize + padding;
}

