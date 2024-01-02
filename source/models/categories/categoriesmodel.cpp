#include "categoriesmodel.h"

CategoriesModel::CategoriesModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int CategoriesModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_categories.size();
}

QVariant CategoriesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto row = index.row();

    if (row >= m_categories.size())
        return QVariant();

    switch (role) {
    case idRole:
        return m_categories.at(row)->m_id;
    case nameRole:
        return m_categories.at(row)->m_name;
    case currencyRole:
        return m_categories.at(row)->m_currency;
    case isIncome:
        return m_categories.at(row)->m_isIncome;
    case iconRole:
        return m_categories.at(row)->m_icon;
    }

    return QVariant();
}

QHash<int, QByteArray> CategoriesModel::roleNames() const
{
    return m_roleNames;
}

void CategoriesModel::initRoleNames()
{
    m_roleNames[idRole] = "id";
    m_roleNames[nameRole] = "name";
    m_roleNames[currencyRole] = "currency";
    m_roleNames[isIncome] = "type";
    m_roleNames[iconRole] = "icon";
}
