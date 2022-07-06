#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "itransaction.h"

#include <QList>
#include <QSharedPointer>
#include <QHash>

class DataStorage : public ITransaction
{
public:

    virtual int addTransaction(QSharedPointer<Transaction> &transaction) override;
    virtual bool updateTransaction(QSharedPointer<Transaction> &transaction) override;
    virtual bool removeTransaction(int id, bool isIncome) override;

    virtual QHash<QString, QList<QSharedPointer<Transaction>>> getTransactions(const QDateTime &from,
                                                                               const QDateTime &to) override;

    virtual QHash<QString, QList<QSharedPointer<Transaction>>> getTransactions(const QDateTime &from,
                                                                               const QDateTime &to,
                                                                               bool isIncome) override;

    DataStorage();
    virtual ~DataStorage();
};

#endif // DATASTORAGE_H
