#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QSharedPointer>

#include "../datastorage/itransaction.h"
#include "itransactionsmanager.h"

class TransactionManager : public QObject, public ITransactionsManager
{
    Q_OBJECT

    Q_PROPERTY(int currentCategory MEMBER m_currentCategory NOTIFY changedCurrentCategory)
    Q_PROPERTY(QList<QSharedPointer<Transaction>> incomeTransactions READ getIncomeTransactions NOTIFY changedCurrentCategory)
    Q_PROPERTY(QList<QSharedPointer<Transaction>> expensesTransactions READ getExpensesTransactions NOTIFY changedCurrentCategory)

public:

    virtual int addTransaction(int category, int account,
                               const QDateTime &date,
                               const QString &text,
                               const qreal &cost,
                               bool isIncome) override;

    virtual bool removeTransaction(int category, bool isIncome, int id) override;

    virtual QList<QSharedPointer<Transaction>> getExpensesTransactions(int category) const override;
    virtual QList<QSharedPointer<Transaction>> getIncomeTransactions(int category) const override;

    virtual bool updateTransaction(int id, int category, int account,
                                   const QDateTime &date,
                                   const QString &text,
                                   const qreal &cost,
                                   bool isIncome) override;

    bool updateRecords(const QDateTime &from, const QDateTime &to);

    QList<QSharedPointer<Transaction>> getIncomeTransactions() const;
    QList<QSharedPointer<Transaction>> getExpensesTransactions() const;

    TransactionManager(ITransaction* dataStorage = nullptr);
    virtual ~TransactionManager();

signals:
    void changedCurrentCategory();

private:
    QHash<int, QList<QSharedPointer<Transaction>>> m_expensesTransactions;
    QHash<int, QList<QSharedPointer<Transaction>>> m_incomeTransactions;
    QHash<int, QList<QSharedPointer<Transaction>>> m_mergeTransactions;
    ITransaction* m_dataStorage = nullptr;

    int m_currentCategory;

    QList<QSharedPointer<Transaction>> getTransactions(int category, bool isIncome) const;
};

#endif // TRANSACTIONMANAGER_H
