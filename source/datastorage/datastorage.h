#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "idatastorage.h"

#include <QList>
#include <QSharedPointer>
#include <QHash>

class DataStorage : public IDataStorage
{
public:

    virtual int addTransaction(QSharedPointer<Transaction> &transaction) override;
    virtual bool updateTransaction(QSharedPointer<Transaction> &transaction) override;
    virtual bool removeTransaction(int id) override;

    virtual QHash<QString, QList<QSharedPointer<Transaction>>> getTransactions(const QDateTime &from,
                                                                               const QDateTime &to) override;

    DataStorage();
    virtual ~DataStorage();
};

#endif // DATASTORAGE_H
