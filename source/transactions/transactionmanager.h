#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QSharedPointer>

#include "../datastorage/idatastorage.h"
#include "itransactionsmanager.h"

class TransactionManager : public QObject, public ITransactionsManager
{
    Q_OBJECT

    Q_PROPERTY(QString currentCategory MEMBER m_currentCategory NOTIFY changedCurrentCategory)
    Q_PROPERTY(QList<QSharedPointer<Transaction>> incomeTransactions READ getIncomeTransactions NOTIFY changedCurrentCategory)
    Q_PROPERTY(QList<QSharedPointer<Transaction>> expensesTransactions READ getExpensesTransactions NOTIFY changedCurrentCategory)

public:

    virtual int addTransaction(const QString &category,
                               const QString &account,
                               const QDateTime &date,
                               const QString &text,
                               const qreal &cost,
                               bool isIncome) override;

    virtual bool removeTransaction(const QString &category, bool isIncome, int id) override;

    virtual QList<QSharedPointer<Transaction>> getExpensesTransactions(const QString &category) const override;
    virtual QList<QSharedPointer<Transaction>> getIncomeTransactions(const QString &category) const override;

    virtual bool updateTransaction(int id,
                                   const QString &category,
                                   const QString &account,
                                   const QDateTime &date,
                                   const QString &text,
                                   const qreal &cost,
                                   bool isIncome) override;

    bool updateRecords(const QDateTime &from, const QDateTime &to);

    QList<QSharedPointer<Transaction>> getIncomeTransactions() const;
    QList<QSharedPointer<Transaction>> getExpensesTransactions() const;

    TransactionManager(IDataStorage* dataStorage = nullptr);
    virtual ~TransactionManager();

signals:
    void changedCurrentCategory();

private:
    QHash<QString, QList<QSharedPointer<Transaction>>> m_expensesTransactions;
    QHash<QString, QList<QSharedPointer<Transaction>>> m_incomeTransactions;
    QHash<QString, QList<QSharedPointer<Transaction>>> m_mergeTransactions;
    IDataStorage* m_dataStorage = nullptr;

    QString m_currentCategory;

    QList<QSharedPointer<Transaction>> getTransactions(const QString &category, bool isIncome) const;
};

#endif // TRANSACTIONMANAGER_H
