#include "datastorage.h"

int DataStorage::addTransaction(QSharedPointer<Transaction> &transaction)
{
    static int temp = 1;
    return temp++;
}

bool DataStorage::updateTransaction(QSharedPointer<Transaction> &transaction)
{
    return true;
}

bool DataStorage::removeTransaction(int id, bool isIncome)
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

DataStorage::DataStorage()
{}

DataStorage::~DataStorage()
{}
