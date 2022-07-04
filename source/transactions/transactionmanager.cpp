#include "transactionmanager.h"

int TransactionManager::addTransaction(const QString &category,
                                       const QString &account,
                                       const QDateTime &date,
                                       const QString &text,
                                       const qreal &cost,
                                       const QString &currency)
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
        newTransaction->currency = currency;

        id = m_dataStorage->addTransaction(newTransaction);
        if(id > 0)
        {
            newTransaction->id = id;
            m_transactions[category].append(newTransaction);
        }
    }
    return id;
}

bool TransactionManager::removeTransaction(const QString &category, int id)
{
    if(m_transactions.contains(category) && m_dataStorage)
    {
        if(!m_dataStorage->removeTransaction(id))
            return false;


        auto &list = m_transactions[category];
        for(int i = 0; i < list.size(); ++i)
        {
            if(list[i]->id == id)
            {
                list.removeAt(i);
                return true;
            }
        }
    }
    return false;
}

QList<QSharedPointer<Transaction>> TransactionManager::getTransactions(const QString &category) const
{
    return m_transactions.contains(category) ? m_transactions[category] : QList<QSharedPointer<Transaction>>();;
}

bool TransactionManager::updateTransaction(int id, const QString &category, const QString &account, const QDateTime &date, const QString &text, const qreal &cost, const QString &currency)
{
    if(m_transactions.contains(category) && m_dataStorage)
    {
        QSharedPointer<Transaction> transcation;

        auto &list = m_transactions[category];
        for(int i = 0; i < list.size(); ++i)
        {
            if(list[i]->id == id)
            {
                transcation = list[i];
                break;
            }
        }

        if(!transcation.isNull() && m_dataStorage->updateTransaction(transcation))
        {
            transcation->id = id;
            transcation->time = date;
            transcation->category = category;
            transcation->account = account;
            transcation->text = text;
            transcation->cost = cost;
            transcation->currency = currency;
            return true;
        }
    }
    return false;
}

bool TransactionManager::updateRecords(const QDateTime &from, const QDateTime &to)
{
    if(m_dataStorage)
    {
        m_transactions = m_dataStorage->getTransactions(from, to);
        return true;
    }
    return false;
}

QList<QSharedPointer<Transaction> > TransactionManager::getCurrentTransactions() const
{
    return getTransactions(m_currentCategory);
}

TransactionManager::TransactionManager(IDataStorage* dataStorage) :
    QObject(nullptr),
    m_dataStorage(dataStorage)
{
}

TransactionManager::~TransactionManager()
{
}
