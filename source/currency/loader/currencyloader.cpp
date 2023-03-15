#include "currencyloader.h"
#include <QNetworkReply>
#include <QFile>

CurrencyLoader::CurrencyLoader(IParser *parser, QObject *parent)
    : QObject{parent}, m_parser{parser}, m_urlData(SOURCE_CURRENCY)
{
    connect(&m_manager, &QNetworkAccessManager::finished, this, &CurrencyLoader::responseHandle);

    if(loadLocalCurrency())
        qDebug() << "Read " << m_currencies.size() << "currencies";
    else
        qDebug() << "Error open " << PATH_LOCAL_CURRENCY;
}

QHash<QString, qreal> CurrencyLoader::getCurrencies() const
{
    return m_currencies;
}

qreal CurrencyLoader::getCurrency(const QString &id) const
{
    return m_currencies.value(id, -1);
}

void CurrencyLoader::refreshCurrencies()
{
    QNetworkRequest request(m_urlData);
    m_manager.get(request);
}

void CurrencyLoader::responseHandle(QNetworkReply *reply)
{
    if(!reply->error())
    {
        auto data = reply->readAll();
        reply->deleteLater();

        if(m_parser)
        {
            m_currencies = m_parser->parse(data);
            saveCurrency(data);

            qDebug() << "Recv " << m_currencies.size() << "currencies";
        }
        else
        {
            qDebug() << "Parser is NULL";
        }
    }
    else
    {
        qDebug() << reply->errorString()
                 << QSslSocket::sslLibraryBuildVersionString()
                 << QSslSocket::supportsSsl()
                 << QSslSocket::sslLibraryVersionString();

        if(m_currencies.isEmpty())
            loadLocalCurrency();
    }
}

bool CurrencyLoader::loadLocalCurrency()
{
    if(!m_parser)
    {
        qDebug() << "Parser is NULL";
        return false;
    }

    QFile file(PATH_LOCAL_CURRENCY);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        m_currencies = m_parser->parse(file.readAll());
        return true;
    }
    else
    {
        return false;
    }
}

bool CurrencyLoader::saveCurrency(const QByteArray &data)
{
    QFile file(PATH_LOCAL_CURRENCY);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(data);
        return true;
    }
    else
    {
        return false;
    }
}
