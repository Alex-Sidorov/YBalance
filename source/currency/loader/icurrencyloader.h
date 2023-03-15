#ifndef ICURRENCYLOADER_H
#define ICURRENCYLOADER_H

#include <QHash>

class ICurrencyLoader
{
public:
    virtual QHash<QString, qreal> getCurrencies() const = 0;
    virtual qreal getCurrency(const QString &id) const = 0;
    virtual void refreshCurrencies() = 0;

    virtual ~ICurrencyLoader() {}
};

#endif // ICURRENCYLOADER_H
