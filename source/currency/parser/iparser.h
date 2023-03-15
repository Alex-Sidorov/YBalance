#ifndef IPARSER_H
#define IPARSER_H

#include <QHash>

class IParser
{
public:
    virtual QHash<QString, qreal> parse(const QByteArray &data) = 0;
    virtual ~IParser(){};
};

#endif // IPARSER_H
