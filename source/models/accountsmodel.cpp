#include "accountsmodel.h"
#include <QDebug>

AccountsModel::AccountsModel(QObject *parent)
    : QAbstractListModel{parent}
{
    initRoleNames();
}

int AccountsModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_accounts.size();
}

QVariant AccountsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto row = index.row();

    if (row >= m_accounts.size())
        return QVariant();

    switch (role) {
    case idRole:
        return m_accounts.at(row)->m_id;
    case nameRole:
        return m_accounts.at(row)->m_name;
    case amountRole:
        return m_accounts.at(row)->m_amount;
    case currencyRole:
        return m_accounts.at(row)->m_currency;
    case typeRole:
        return m_accounts.at(row)->m_type;
    case iconRole:
        return m_accounts.at(row)->m_icon;
    }

    return QVariant();
}

QHash<int, QByteArray> AccountsModel::roleNames() const
{
    return m_roleNames;
}

void AccountsModel::addAccount(const QSharedPointer<Account> &account)
{
    beginInsertRows(QModelIndex(), m_accounts.size(), m_accounts.size());
    m_accounts.push_back(account);
    endInsertRows();
}

void AccountsModel::removeAccount(int id)
{
    for(int i = 0; i < m_accounts.size(); ++i)
    {
        if(m_accounts[i]->m_id == id)
        {
            beginRemoveRows(QModelIndex(), i, i);
            m_accounts.removeAt(i);
            endRemoveRows();
            break;
        }
    }
}

void AccountsModel::initRoleNames()
{
    m_roleNames[idRole] = "id";
    m_roleNames[nameRole] = "name";
    m_roleNames[amountRole] = "amount";
    m_roleNames[currencyRole] = "currency";
    m_roleNames[typeRole] = "type";
    m_roleNames[iconRole] = "icon";
}
