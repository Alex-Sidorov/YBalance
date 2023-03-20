#ifndef ICURRENCYSTORAGE_H
#define ICURRENCYSTORAGE_H

#include <QStringList>

class ICurrencyStorage
{
public:
    virtual ~ICurrencyStorage(){}

    virtual QStringList getCurrencyList() const = 0;

};

#endif // ICURRENCYSTORAGE_H
