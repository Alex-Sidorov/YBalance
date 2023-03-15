#ifndef CURRENCYLOADER_H
#define CURRENCYLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>

#include "icurrencyloader.h"
#include "../parser/iparser.h"

class CurrencyLoader : public QObject, public ICurrencyLoader
{
    Q_OBJECT

public:
    explicit CurrencyLoader(IParser *parser, QObject *parent = nullptr);
    virtual ~CurrencyLoader(){}

    virtual QHash<QString, qreal> getCurrencies() const override;
    virtual qreal getCurrency(const QString &id) const override;
    virtual void refreshCurrencies() override;


private slots:
    void responseHandle(QNetworkReply *reply);

private:
    QNetworkAccessManager m_manager;

    IParser *m_parser = nullptr;

    const QString SOURCE_CURRENCY = "https://www.cbr-xml-daily.ru/daily_json.js";
    const QString PATH_LOCAL_CURRENCY = "currency/currency.json";

    QUrl m_urlData;

    QHash<QString, qreal> m_currencies;
    bool loadLocalCurrency();
    bool saveCurrency(const QByteArray &data);
};

#endif // CURRENCYLOADER_H
