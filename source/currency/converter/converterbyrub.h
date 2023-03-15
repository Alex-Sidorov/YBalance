#ifndef CONVERTERBYRUB_H
#define CONVERTERBYRUB_H

#include <QObject>

#include "iconverter.h"
#include "../loader/icurrencyloader.h"

class ConverterByRUB : public QObject, public IConverter
{
    Q_OBJECT

public:
    explicit ConverterByRUB(ICurrencyLoader *currencyLoader, QObject *parent = nullptr);
    virtual ~ConverterByRUB() {}

    virtual qreal convert(const QString& from, const QString& to, const qreal value) const override;

private:
    ICurrencyLoader* m_currencyLoader;
};

#endif // CONVERTERBYRUB_H
