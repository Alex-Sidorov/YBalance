#ifndef ITRANSACTION_H
#define ITRANSACTION_H

#include "../transactions/transaction.h"

#include <QHash>

class ITransaction
{
public:

    virtual int addTransaction(QSharedPointer<Transaction> &transaction) = 0;
    virtual bool updateTransaction(QSharedPointer<Transaction> &transaction) = 0;
    virtual bool removeTransaction(int id, bool isIncome) = 0;

    virtual QHash<QString, QList<QSharedPointer<Transaction>>> getTransactions(const QDateTime &from,
                                                                               const QDateTime &to) = 0;

    virtual QHash<QString, QList<QSharedPointer<Transaction>>> getTransactions(const QDateTime &from,
                                                                               const QDateTime &to,
                                                                               bool isIncome) = 0;

    virtual ~ITransaction() {}
};

#endif // ITRANSACTION_H
