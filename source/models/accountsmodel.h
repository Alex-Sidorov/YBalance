#ifndef ACCOUNTSMODEL_H
#define ACCOUNTSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QSharedPointer>
#include <QHash>

#include "../accounts/iaccountmanager.h"

class AccountsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ rowCount NOTIFY updatedModel)

    enum {
        idRole,
        nameRole,
        amountRole,
        currencyRole,
        typeRole,
        iconRole
    };

public:
    explicit AccountsModel(QObject *parent = nullptr);
    virtual ~AccountsModel(){}


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    void addAccount(const QSharedPointer<Account> &account);
    void removeAccount(int id);

signals:
    void updatedModel();

private:
    QList<QSharedPointer<Account>> m_accounts;
    QHash<int, QByteArray> m_roleNames;

    void initRoleNames();
};

#endif // ACCOUNTSMODEL_H
