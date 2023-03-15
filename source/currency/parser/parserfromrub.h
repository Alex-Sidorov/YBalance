#ifndef PARSERFROMRUB_H
#define PARSERFROMRUB_H

#include "iparser.h"

class ParserFromRUB : public IParser
{
public:
    ParserFromRUB();
    virtual ~ParserFromRUB() {}

    virtual QHash<QString, qreal> parse(const QByteArray &data) override;
};

#endif // PARSERFROMRUB_H
