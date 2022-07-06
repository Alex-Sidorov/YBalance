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
                               bool isIncome) = 0;

    virtual bool removeTransaction(const QString &category, bool isIncome, int id) = 0;

    virtual QList<QSharedPointer<Transaction>> getIncomeTransactions(const QString &category) const = 0;
    virtual QList<QSharedPointer<Transaction>> getExpensesTransactions(const QString &category) const = 0;
    virtual bool updateTransaction(int id,
                                   const QString &category,
                                   const QString &account,
                                   const QDateTime &date,
                                   const QString &text,
                                   const qreal &cost,
                                   bool isIncome) = 0;

    virtual ~ITransactionsManager(){}
};

#endif // ITRANSACTIONSMANAGER_H
