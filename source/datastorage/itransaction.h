#ifndef ITRANSACTION_H
#define ITRANSACTION_H

#include "../transactions/transaction.h"

#include <QHash>

class ITransaction
{
public:

    virtual int addTransaction(QSharedPointer<Transaction> &transaction) = 0;
    virtual bool updateTransaction(int id, int category, int account,
                                   const QDateTime &date,
                                   const QString &text,
                                   const qreal &cost,
                                   bool isIncome) = 0;

    virtual bool removeTransaction(int id) = 0;

    virtual QHash<int, QList<QSharedPointer<Transaction>>> getTransactions(const QDateTime &from,
                                                                           const QDateTime &to,
                                                                           QObject *parent) = 0;

    virtual QHash<int, QList<QSharedPointer<Transaction>>> getTransactions(const QDateTime &from,
                                                                           const QDateTime &to,
                                                                           bool isIncome,
                                                                           QObject *parent) = 0;

    virtual ~ITransaction() {}
};

#endif // ITRANSACTION_H
