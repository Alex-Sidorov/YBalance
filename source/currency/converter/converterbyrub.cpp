#include "converterbyrub.h"
#include <QDebug>

ConverterByRUB::ConverterByRUB(ICurrencyLoader *currencyLoader)
    : m_currencyLoader{currencyLoader}
{}

qreal ConverterByRUB::convert(const QString &from, const QString &to, const qreal value) const
{
    if(!m_currencyLoader)
        return -1;

    auto fromValue = m_currencyLoader->getCurrency(from);
    auto toValue = m_currencyLoader->getCurrency(to);

    if(toValue < 0 || fromValue < 0)
    {
        qDebug() << "Not found currency: "
                 << from << "=" << fromValue
                 << " "
                 << to << "=" << toValue;
        return -1;
    }

    return (fromValue * value) / toValue;
}
