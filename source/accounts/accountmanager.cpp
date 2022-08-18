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

int AccountManager::addAccount(const QString &name,
                               const QDateTime &date,
                               const QString &currency,
                               const qreal amount,
                               const QString &icon,
                               const QString &color,
                               AccountType::Type type)
{
    QSharedPointer<Account> account(new Account(name, date, currency, amount, icon, color, type, this));

    if(m_accounts.size())
        account->m_id = m_accounts.last()->m_id + 1;

    if(m_dataStorage && m_dataStorage->addAccount(account.data()))
        return -1;

    m_accounts << account;
    m_hashAccounts[account->m_id] = account;

    return account->m_id;
}

bool AccountManager::removeAccount(int id)
{
    auto account = m_hashAccounts.value(id, QSharedPointer<Account>(nullptr));

    if(account.isNull())
        return false;

    if(m_dataStorage && !m_dataStorage->removeAccount(account->m_id))
        return false;

    m_hashAccounts.remove(account->m_id);
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

bool AccountManager::updateAccount(int id,
                                   const qreal amount,
                                   const QString &name,
                                   const QString &currency,
                                   const QString &icon,
                                   const QString &color,
                                   AccountType::Type type)
{
    auto account = m_hashAccounts.value(id, QSharedPointer<Account>(nullptr));

    if(!m_dataStorage || account.isNull())
        return false;

    if(!m_dataStorage->updateAccount(id, amount, name, currency, icon, color, type))
        return false;

    account->m_amount = amount;
    account->m_name = name;;
    account->m_currency = currency;
    account->m_icon = icon;
    account->m_color = color;
    account->m_type = type;

    return true;
}

bool AccountManager::addAmount(int id, qreal value)
{
    auto account = m_hashAccounts.value(id, QSharedPointer<Account>(nullptr));

    if(account.isNull())
        return false;

    auto amount = account->m_amount + value;
    return updateAmount(account.data(), amount);
}

bool AccountManager::subAmount(int id, qreal value)
{
    auto account = m_hashAccounts.value(id, QSharedPointer<Account>(nullptr));

    if(account.isNull())
        return false;

    auto amount = account->m_amount - value;
    return updateAmount(account.data(), amount);
}

bool AccountManager::updateAmount(Account *account, qreal amount)
{
    if(account && m_dataStorage && !m_dataStorage->updateAmount(account->m_id, amount))
        return false;

    account->m_amount = amount;
    return true;
}
