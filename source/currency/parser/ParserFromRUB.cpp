#include "parserfromrub.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ParserFromRUB::ParserFromRUB()
{}

QHash<QString, qreal> ParserFromRUB::parse(const QByteArray &data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();

    QJsonObject valuteObj = jsonObj["Valute"].toObject();
    auto valuteKeys = valuteObj.keys();

    QHash<QString, qreal> currencies;

    for (const auto& valute : valuteKeys)
    {
        QJsonObject valuteItemObj = valuteObj[valute].toObject();

        auto nominal = valuteItemObj["Nominal"].toInt();
        auto value = valuteItemObj["Value"].toDouble();

        currencies[valute] = value / nominal;
    }

    if(currencies.isEmpty() == false)
        currencies["RUB"] = 1;

    qDebug() << "Date update currency:" << jsonObj["Date"].toString();

    return currencies;
}
