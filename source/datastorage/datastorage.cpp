#include "datastorage.h"

int DataStorage::addTransaction(QSharedPointer<Transaction> &transaction)
{
    static int temp = 1;
    return temp++;
}

bool DataStorage::updateTransaction(int id, const QString &category,
                                    const QString &account,
                                    const QDateTime &date,
                                    const QString &text,
                                    const qreal &cost,
                                    bool isIncome)
{
    return true;
}

bool DataStorage::removeTransaction(int id)
{
    return true;
}

QHash<QString, QList<QSharedPointer<Transaction>>> DataStorage::getTransactions(const QDateTime &from,
                                                                                const QDateTime &to)
{
    return QHash<QString, QList<QSharedPointer<Transaction>>>();
}

QHash<QString, QList<QSharedPointer<Transaction>>> DataStorage::getTransactions(const QDateTime &from,
                                                                                const QDateTime &to,
                                                                                bool isIncome)
{
    return QHash<QString, QList<QSharedPointer<Transaction>>>();
}

bool DataStorage::readAccounts(QPair<AccountsList*, AccountsHash*> &accounts)
{

}

bool DataStorage::addAccount(Account *account)
{

}

bool DataStorage::updateAccount(int id, const qreal amount, const QString &name, const QString &currency, const QString &icon, const QString &color, AccountType::Type type)
{

}

bool DataStorage::removeAccount(int id)
{

}

bool DataStorage::updateAmount(int id, qreal amount)
{

}

DataStorage::DataStorage()
{}

DataStorage::~DataStorage()
{}
