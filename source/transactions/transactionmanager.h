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
    Q_PROPERTY(QList<QSharedPointer<Transaction>> currentTransactions READ getCurrentTransactions NOTIFY changedCurrentCategory)

public:

    virtual int addTransaction(const QString &category,
                               const QString &account,
                               const QDateTime &date,
                               const QString &text,
                               const qreal &cost,
                               const QString &currency) override;

    virtual bool removeTransaction(const QString &category, int id) override;

    virtual QList<QSharedPointer<Transaction>> getTransactions(const QString &category) const override;

    virtual bool updateTransaction(int id,
                                   const QString &category,
                                   const QString &account,
                                   const QDateTime &date,
                                   const QString &text,
                                   const qreal &cost,
                                   const QString &currency) override;

    bool updateRecords(const QDateTime &from, const QDateTime &to);

    QList<QSharedPointer<Transaction>> getCurrentTransactions() const;

    TransactionManager(IDataStorage* dataStorage = nullptr);
    virtual ~TransactionManager();

signals:
    void changedCurrentCategory();

private:
    QHash<QString, QList<QSharedPointer<Transaction>>> m_transactions;
    IDataStorage* m_dataStorage = nullptr;

    QString m_currentCategory;
};

#endif // TRANSACTIONMANAGER_H
