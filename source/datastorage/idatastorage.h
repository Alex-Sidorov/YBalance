#ifndef IDATASTORAGE_H
#define IDATASTORAGE_H

#include "../transactions/transaction.h"

#include <QHash>

class IDataStorage
{
public:

    virtual int addTransaction(QSharedPointer<Transaction> &transaction) = 0;
    virtual bool updateTransaction(QSharedPointer<Transaction> &transaction) = 0;
    virtual bool removeTransaction(int id) = 0;

    virtual QHash<QString, QList<QSharedPointer<Transaction>>> getTransactions(const QDateTime &from,
                                                                               const QDateTime &to) = 0;

    virtual ~IDataStorage() {}
};

#endif // IDATASTORAGE_H
