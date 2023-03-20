#ifndef CONVERTERBYRUB_H
#define CONVERTERBYRUB_H

#include "iconverter.h"
#include "../loader/icurrencyloader.h"

class ConverterByRUB : public IConverter
{
public:
    explicit ConverterByRUB(ICurrencyLoader *currencyLoader);
    virtual ~ConverterByRUB() {}

    virtual qreal convert(const QString& from, const QString& to, const qreal value) const override;

private:
    ICurrencyLoader* m_currencyLoader;
};

#endif // CONVERTERBYRUB_H
