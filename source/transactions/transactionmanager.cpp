#include "transactionmanager.h"

int TransactionManager::addTransaction(int category,
                                       int account,
                                       const QDateTime &date,
                                       const QString &text,
                                       const qreal &cost,
                                       bool isIncome)
{
    int id = -1;
    if(m_dataStorage)
    {
        QSharedPointer<Transaction> newTransaction(new Transaction(category, account,
                                                                   date, text, cost,
                                                                   isIncome, this));
        id = m_dataStorage->addTransaction(newTransaction);
        if(id >= 0)
        {
            newTransaction->m_id = id;
            if(isIncome)
                m_incomeTransactions[category].append(newTransaction);
            else
                m_expensesTransactions[category].append(newTransaction);

            m_mergeTransactions[category].append(newTransaction);
        }
    }
    return id;
}

bool TransactionManager::removeTransaction(int category, bool isIncome, int id)
{
    auto &transactions = isIncome ? m_incomeTransactions : m_expensesTransactions;
    if(transactions.contains(category) && m_dataStorage)
    {
        if(!m_dataStorage->removeTransaction(id))
            return false;

        auto &list = transactions[category];
        for(int i = 0; i < list.size(); ++i)
        {
            if(list[i]->m_id == id)
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

QList<QSharedPointer<Transaction> > TransactionManager::getIncomeTransactions(int category) const
{
    return getTransactions(category, true);
}

QList<QSharedPointer<Transaction> > TransactionManager::getExpensesTransactions(int category) const
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

QList<QSharedPointer<Transaction>> TransactionManager::getTransactions(int category, bool isIncome) const
{
    if(isIncome)
        return m_incomeTransactions.contains(category) ? m_incomeTransactions[category] : QList<QSharedPointer<Transaction>>();
    else
        return m_expensesTransactions.contains(category) ? m_expensesTransactions[category] : QList<QSharedPointer<Transaction>>();
}

bool TransactionManager::updateTransaction(int id, int category, int account,
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
            if(list[i]->m_id == id)
            {
                transaction = list[i];
                break;
            }
        }

        if(!transaction.isNull() && m_dataStorage->updateTransaction(id, category,
                                                                     account, date,
                                                                     text, cost,
                                                                     isIncome))
        {
            transaction->m_time = date;
            transaction->m_category = category;
            transaction->m_account = account;
            transaction->m_text = text;
            transaction->m_cost = cost;
            transaction->m_isIncome = isIncome;
            return true;
        }
    }
    return false;
}

bool TransactionManager::updateRecords(const QDateTime &from, const QDateTime &to)
{
    if(m_dataStorage)
    {
        m_incomeTransactions = m_dataStorage->getTransactions(from, to, true, this);
        m_expensesTransactions = m_dataStorage->getTransactions(from, to, false, this);
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
