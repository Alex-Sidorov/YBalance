#ifndef ITRANSACTIONSMANAGER_H
#define ITRANSACTIONSMANAGER_H

#include <QList>
#include <QSharedPointer>
#include "transaction.h"

class ITransactionsManager
{
public:

    virtual int addTransaction(const QString &category,
                               const QString &account,
                               const QDateTime &date,
                               const QString &text,
                               const qreal &cost,
                               const QString &currency) = 0;

    virtual bool removeTransaction(const QString &category, int id) = 0;

    virtual QList<QSharedPointer<Transaction>> getTransactions(const QString &category) const = 0;
    virtual bool updateTransaction(int id,
                                   const QString &category,
                                   const QString &account,
                                   const QDateTime &date,
                                   const QString &text,
                                   const qreal &cost,
                                   const QString &currency) = 0;

    virtual ~ITransactionsManager(){}
};

#endif // ITRANSACTIONSMANAGER_H
