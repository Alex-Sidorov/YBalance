#ifndef ITRANSACTIONSMANAGER_H
#define ITRANSACTIONSMANAGER_H

#include <QList>
#include <QSharedPointer>
#include "transaction.h"

class ITransactionsManager
{
public:

    virtual int addTransaction(const int category,
                               const int account,
                               const QDateTime &date,
                               const QString &text,
                               const qreal &cost,
                               bool isIncome) = 0;

    virtual bool removeTransaction(int category, bool isIncome, int id) = 0;

    virtual QList<QSharedPointer<Transaction>> getIncomeTransactions(int category) const = 0;
    virtual QList<QSharedPointer<Transaction>> getExpensesTransactions(int category) const = 0;
    virtual bool updateTransaction(int id, int category, int account,
                                   const QDateTime &date,
                                   const QString &text,
                                   const qreal &cost,
                                   bool isIncome) = 0;

    virtual ~ITransactionsManager(){}
};

#endif // ITRANSACTIONSMANAGER_H
