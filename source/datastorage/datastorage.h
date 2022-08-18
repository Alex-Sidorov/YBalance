#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "itransaction.h"
#include "iaccount.h"

#include <QList>
#include <QSharedPointer>
#include <QHash>

class DataStorage : public ITransaction, public IAccount
{
public:

    virtual int addTransaction(QSharedPointer<Transaction> &transaction) override;
    virtual bool updateTransaction(int id, const QString &category,
                                   const QString &account,
                                   const QDateTime &date,
                                   const QString &text,
                                   const qreal &cost,
                                   bool isIncome) override;
    virtual bool removeTransaction(int id) override;

    virtual QHash<QString, QList<QSharedPointer<Transaction>>> getTransactions(const QDateTime &from,
                                                                               const QDateTime &to) override;

    virtual QHash<QString, QList<QSharedPointer<Transaction>>> getTransactions(const QDateTime &from,
                                                                               const QDateTime &to,
                                                                               bool isIncome) override;

    virtual bool readAccounts(QPair< AccountsList*, AccountsHash*> &accounts) override;

    virtual bool addAccount(Account * account) override;
    virtual bool updateAccount(int id, const qreal amount, const QString &name, const QString &currency, const QString &icon, const QString &color, AccountType::Type type) override;
    virtual bool removeAccount(int id) override;

    virtual bool updateAmount(int id, qreal amount) override;

    DataStorage();
    virtual ~DataStorage();
};

#endif // DATASTORAGE_H
