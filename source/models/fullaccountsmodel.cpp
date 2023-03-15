#include "fullaccountsmodel.h"
#include <QDebug>

FullAccountsModel::FullAccountsModel(IAccountManager* manager, QObject *parent)
    : QObject{parent}, m_accountManager{manager}
{
    if(initAccountsModels())
    {
        qDebug() << "Init Full Accounts Model: "
                 << "CASH:" << m_cashAccounts.rowCount()
                 << "CARD:" << m_cardAccounts.rowCount()
                 << "DEBT:" << m_debtAccounts.rowCount()
                 << "SAVINGS:" << m_savingsAccounts.rowCount();
    }
    else
    {
        qDebug() << "Error Init Full Accounts Model";
    }
}

const AccountsModel *FullAccountsModel::getCashAccounts() const
{
    return &m_cashAccounts;
}

const AccountsModel *FullAccountsModel::getCardAccounts() const
{
    return &m_cardAccounts;
}

const AccountsModel *FullAccountsModel::getDebtAccounts() const
{
    return &m_debtAccounts;
}

const AccountsModel *FullAccountsModel::getSavingsAccounts() const
{
    return &m_savingsAccounts;
}

bool FullAccountsModel::addAccount(const QString &name, const QString &currency, const qreal amount, const QString &icon, const QString &color, AccountType::Type type)
{
    if(!m_accountManager)
        return false;

    auto id = m_accountManager->addAccount(name, currency, amount, icon, color, type);
    if(id == -1)
    {
        qDebug() << "Error add new account: name=" << name;
        return false;
    }

    auto newAccount = m_accountManager->getAccount(id);
    if(newAccount.isNull())
    {
        qDebug() << "Error get account. Account is NULL";
        return false;
    }

    addAccount(newAccount);

    return true;
}

bool FullAccountsModel::updateAccount(int id, const qreal amount, const QString &name, const QString &currency, const QString &icon, const QString &color, AccountType::Type type)
{
    if(!m_accountManager)
        return false;

    auto result = m_accountManager->updateAccount(id, amount, name, currency, icon, color, type);
    if(!result)
    {
        qDebug() << "Error update account: id=" << id << " name=" <<name;
        return false;
    }

    return true;
}

bool FullAccountsModel::removeAccount(int id)
{
    if(!m_accountManager)
        return false;

    auto account = m_accountManager->getAccount(id);
    if(account.isNull())
    {
        qDebug() << "Error get account. Account is NULL";
        return false;
    }

    auto result = m_accountManager->removeAccount(id);
    if(!result)
    {
        qDebug() << "Error remove account: id=" << id;
        return false;
    }

    removeAccount(account);

    return true;
}

bool FullAccountsModel::initAccountsModels()
{
    if(!m_accountManager)
        return false;

    const auto& allAccounts = m_accountManager->getAccounts();
    for(const auto& account : allAccounts)
    {
        if(!account.isNull())
            addAccount(account);
    }

    return true;
}

void FullAccountsModel::addAccount(const QSharedPointer<Account> &account)
{
    auto type = account->m_type;

    if(type == AccountType::CARD)
        m_cardAccounts.addAccount(account);
    else if(type == AccountType::CASH)
        m_cashAccounts.addAccount(account);
    else if(type == AccountType::DEBT)
        m_debtAccounts.addAccount(account);
    else if(type == AccountType::SAVINGS)
        m_savingsAccounts.addAccount(account);
}

void FullAccountsModel::removeAccount(const QSharedPointer<Account> &account)
{
    auto type = account->m_type;
    auto id = account->m_id;

    if(type == AccountType::CARD)
        m_cardAccounts.removeAccount(id);
    else if(type == AccountType::CASH)
        m_cashAccounts.removeAccount(id);
    else if(type == AccountType::DEBT)
        m_debtAccounts.removeAccount(id);
    else if(type == AccountType::SAVINGS)
        m_savingsAccounts.removeAccount(id);
}
