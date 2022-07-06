#include "transactionmanager.h"

int TransactionManager::addTransaction(const QString &category,
                                       const QString &account,
                                       const QDateTime &date,
                                       const QString &text,
                                       const qreal &cost,
                                       bool isIncome)
{
    int id = -1;
    if(m_dataStorage)
    {
        QSharedPointer<Transaction> newTransaction(new Transaction(this));
        newTransaction->time = date;
        newTransaction->category = category;
        newTransaction->account = account;
        newTransaction->text = text;
        newTransaction->cost = cost;
        newTransaction->isIncome = isIncome;

        id = m_dataStorage->addTransaction(newTransaction);
        if(id > 0)
        {
            newTransaction->id = id;
            if(isIncome)
                m_incomeTransactions[category].append(newTransaction);
            else
                m_expensesTransactions[category].append(newTransaction);

            m_mergeTransactions[category].append(newTransaction);
        }
    }
    return id;
}

bool TransactionManager::removeTransaction(const QString &category, bool isIncome, int id)
{
    auto &transactions = isIncome ? m_incomeTransactions : m_expensesTransactions;
    if(transactions.contains(category) && m_dataStorage)
    {
        if(!m_dataStorage->removeTransaction(id, isIncome))
            return false;

        auto &list = transactions[category];
        for(int i = 0; i < list.size(); ++i)
        {
            if(list[i]->id == id)
            {
                auto &fullList = m_mergeTransactions[category];
                fullList.removeAll(list[i]);
                list.removeAt(i);
                return true;
            }
        }
    }
    return false;
}

QList<QSharedPointer<Transaction> > TransactionManager::getIncomeTransactions(const QString &category) const
{
    return getTransactions(category, true);
}

QList<QSharedPointer<Transaction> > TransactionManager::getExpensesTransactions(const QString &category) const
{
    return getTransactions(category, false);
}

QList<QSharedPointer<Transaction> > TransactionManager::getIncomeTransactions() const
{
    return getTransactions(m_currentCategory, true);
}

QList<QSharedPointer<Transaction> > TransactionManager::getExpensesTransactions() const
{
    return getTransactions(m_currentCategory, true);
}

QList<QSharedPointer<Transaction>> TransactionManager::getTransactions(const QString &category, bool isIncome) const
{
    if(isIncome)
        return m_incomeTransactions.contains(category) ? m_incomeTransactions[category] : QList<QSharedPointer<Transaction>>();
    else
        return m_expensesTransactions.contains(category) ? m_expensesTransactions[category] : QList<QSharedPointer<Transaction>>();
}

bool TransactionManager::updateTransaction(int id, const QString &category,
                                           const QString &account,
                                           const QDateTime &date,
                                           const QString &text,
                                           const qreal &cost,
                                           bool isIncome)
{
    auto &transactions = isIncome ? m_incomeTransactions : m_expensesTransactions;
    if(transactions.contains(category) && m_dataStorage)
    {
        QSharedPointer<Transaction> transaction;

        auto &list = transactions[category];
        for(int i = 0; i < list.size(); ++i)
        {
            if(list[i]->id == id)
            {
                transaction = list[i];
                break;
            }
        }

        if(!transaction.isNull() && m_dataStorage->updateTransaction(transaction))
        {
            transaction->id = id;
            transaction->time = date;
            transaction->category = category;
            transaction->account = account;
            transaction->text = text;
            transaction->cost = cost;
            transaction->isIncome = isIncome;
            return true;
        }
    }
    return false;
}

bool TransactionManager::updateRecords(const QDateTime &from, const QDateTime &to)
{
    if(m_dataStorage)
    {
        m_incomeTransactions = m_dataStorage->getTransactions(from, to, true);
        m_expensesTransactions = m_dataStorage->getTransactions(from, to, false);
        return true;
    }
    return false;
}

TransactionManager::TransactionManager(ITransaction* dataStorage) :
    QObject(nullptr),
    m_dataStorage(dataStorage)
{
}

TransactionManager::~TransactionManager()
{
}
