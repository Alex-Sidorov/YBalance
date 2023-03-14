#ifndef ACCOUNTSMODEL_H
#define ACCOUNTSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QSharedPointer>

#include "../accounts/iaccountmanager.h"

class AccountsModel : public QAbstractListModel
{
    Q_OBJECT

    enum {
        idRole,
        nameRole,
        amountRole,
        currencyRole,
        typeRole,
        iconRole,
        colorRole,
    };

public:
    explicit AccountsModel(QObject *parent = nullptr);
    virtual ~AccountsModel(){}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    void addAccount(const QSharedPointer<Account> &account);
    void removeAccount(int id);

private:
    QList<QSharedPointer<Account>> m_accounts;
    QHash<int, QByteArray> m_roleNames;

    void initRoleNames();
};

#endif // ACCOUNTSMODEL_H
