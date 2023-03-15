#ifndef ICONVERTER_H
#define ICONVERTER_H

#include <QString>

class IConverter
{
public:
    /**
     * @brief convert
     * @param from - id currency
     * @param to - id currency
     * @param value - value for convert
     * @return result of convert
     */
    virtual qreal convert(const QString& from, const QString& to, const qreal value) const = 0;

    virtual ~IConverter(){}
};

#endif // ICONVERTER_H
