#include "currencystorage.h"

CurrencyStorage::CurrencyStorage(QObject *parent)
    : QObject{parent}
{

}

QStringList CurrencyStorage::getCurrencyList() const
{
    return CURRENCY;
}
