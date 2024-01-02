#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "itransaction.h"
#include "iaccount.h"
#include "icategories.h"

#include <QList>
#include <QSharedPointer>
#include <QHash>
#include <QSqlDatabase>

class DataStorage : public ITransaction, public IAccount, public ICategories
{
public:

    virtual int addTransaction(QSharedPointer<Transaction> &transaction) override;
    virtual bool updateTransaction(int id, int category, int account,
                                   const QDateTime &date,
                                   const QString &text,
                                   const qreal &cost,
                                   bool isIncome) override;

    virtual bool removeTransaction(int id) override;

    virtual QHash<int, QList<QSharedPointer<Transaction>>> getTransactions(const QDateTime &from,
                                                                           const QDateTime &to,
                                                                           QObject *parent = nullptr) override;

    virtual QHash<int, QList<QSharedPointer<Transaction>>> getTransactions(const QDateTime &from,
                                                                           const QDateTime &to,
                                                                           bool isIncome,
                                                                           QObject *parent = nullptr) override;

    virtual bool readAccounts(QPair< AccountsList*, AccountsHash*> &accounts, QObject* parent = nullptr) override;

    virtual bool addAccount(Account * account) override;
    virtual bool updateAccount(int id, const qreal amount, const QString &name, const QString &currency,
                               const QString &icon, AccountType::Type type) override;
    virtual bool removeAccount(int id) override;

    virtual bool updateAmount(int id, qreal amount) override;

    virtual bool addCategory(const QSharedPointer<Category> &category) override;
    virtual bool removeCategory(const int id) override;
    virtual bool updateCategory(const int id, const QString &name, const QString &currency, const QString &icon, const bool isIncome) override;
    virtual void getCategories(QPair< CategoryList*, CategoryHash*> &categories, bool isIncome, QObject* parent = nullptr) override;

    DataStorage();
    virtual ~DataStorage();

private:
    QSqlDatabase m_database;

    const QString DATA_BASE = "database/database.db";
    const QString BASE_SCRIPT = "database/database.sql";

    bool execScript();

    void readTransactions(QSqlQuery &query,
                          QHash<int, QList<QSharedPointer<Transaction>>> &transactions,
                          QObject* parent = nullptr);

    void parseCategories(QSqlQuery &query, CategoryList* list, CategoryHash* hash, QObject *parent);
};

#endif // DATASTORAGE_H
