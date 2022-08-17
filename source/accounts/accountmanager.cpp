#include "accountmanager.h"
#include <QDebug>

AccountManager::AccountManager(IAccount * dataStorage) : QObject(nullptr), m_dataStorage(dataStorage)
{
    if(!m_dataStorage)
        return;

    auto pair = qMakePair(&m_accounts, &m_hashAccounts);

    auto result = m_dataStorage->readAccounts(pair);
    if(result)
        qDebug() << "readed accounts: " << m_accounts.size();
    else
        qDebug() << "error reading accounts";
}

AccountManager::~AccountManager()
{
}

int AccountManager::addAccount(const QString &name, const QDateTime &date, const QString &currency, const qreal amount, const QString &icon, const QString &color, AccountType::Type type)
{
    QSharedPointer<Account> account(new Account(this));

    if(m_dataStorage && m_dataStorage->addAccount(account.data()))
        return -1;

    account->time = date;
    account->amount = amount;
    account->name = name;;
    account->currency = currency;
    account->icon = icon;
    account->color = color;
    account->id = m_accounts.size();
    account->type = type;

    m_accounts << account;

    m_hashAccounts[account->id] = account;

    return account->id;
}

bool AccountManager::removeAccount(int id)
{
    auto account = m_hashAccounts.value(id, QSharedPointer<Account>(nullptr));

    if(account.isNull())
        return false;

    if(m_dataStorage && !m_dataStorage->removeAccount(account->id))
        return false;

    m_hashAccounts.remove(account->id);
    m_accounts.removeAll(account);

    return true;
}

QList<QSharedPointer<Account> > AccountManager::getAccounts() const
{
    return m_accounts;
}

Account *AccountManager::getAccount(int id) const
{
    return m_hashAccounts.value(id, QSharedPointer<Account>(nullptr)).data();
}

bool AccountManager::updateAccount(int id, const qreal amount, const QString &name, const QString &currency, const QString &icon, const QString &color, AccountType::Type type)
{
    auto account = m_hashAccounts.value(id, QSharedPointer<Account>(nullptr));

    if(account.isNull())
        return false;

    if(m_dataStorage && !m_dataStorage->updateAccount(id, amount, name, currency, icon, color, type))
        return false;

    account->amount = amount;
    account->name = name;;
    account->currency = currency;
    account->icon = icon;
    account->color = color;
    account->id = m_accounts.size();
    account->type = type;

    return true;
}

bool AccountManager::addAmount(int id, qreal value)
{
    auto account = m_hashAccounts.value(id, QSharedPointer<Account>(nullptr));

    if(account.isNull())
        return false;

    auto amount = account->amount + value;
    return updateAmount(account.data(), amount);
}

bool AccountManager::subAmount(int id, qreal value)
{
    auto account = m_hashAccounts.value(id, QSharedPointer<Account>(nullptr));

    if(account.isNull())
        return false;

    auto amount = account->amount - value;
    return updateAmount(account.data(), amount);
}

bool AccountManager::updateAmount(Account *account, qreal amount)
{
    if(m_dataStorage && !m_dataStorage->updateAmount(account->id, amount))
        return false;

    account->amount = amount;
    return true;
}
