#ifndef CURRENCYSTORAGE_H
#define CURRENCYSTORAGE_H

#include <QObject>

#include "icurrencystorage.h"

class CurrencyStorage : public QObject, public ICurrencyStorage
{
    Q_OBJECT

public:
    explicit CurrencyStorage(QObject *parent = nullptr);
    virtual ~CurrencyStorage() {}

    Q_INVOKABLE virtual QStringList getCurrencyList() const;

private:

    inline static const QStringList CURRENCY {
        "AZN", "EGP", "SGD", "QAR", "PLN", "TRY",
        "BRL", "SEK", "THB", "UAH", "CZK", "NZD", "BYN",
        "HKD", "GBP", "CAD", "RSD", "RUB", "AMD", "KZT",
        "UZS", "USD", "CNY", "TMT", "HUF", "INR", "VND",
        "IDR", "RON", "DKK", "AUD", "CHF", "KRW", "BGN",
        "AED", "NOK", "KGS", "TJS", "XDR", "GEL", "ZAR",
        "MDL", "EUR", "JPY"
    };

};

#endif // CURRENCYSTORAGE_H
