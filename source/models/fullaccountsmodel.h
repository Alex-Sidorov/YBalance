#ifndef FULLACCOUNTSMODEL_H
#define FULLACCOUNTSMODEL_H

#include <QObject>

#include "../accounts/iaccountmanager.h"
#include "accountsmodel.h"

class FullAccountsModel : public QObject
{
    Q_OBJECT

public:
    explicit FullAccountsModel(IAccountManager* manager, QObject *parent = nullptr);
    virtual ~FullAccountsModel(){}


    Q_INVOKABLE AccountsModel* getCashAccounts();
    Q_INVOKABLE AccountsModel* getCardAccounts();
    Q_INVOKABLE AccountsModel* getDebtAccounts();
    Q_INVOKABLE AccountsModel* getSavingsAccounts();

    Q_INVOKABLE bool addAccount(const QString &name,
                                const QString &currency,
                                const qreal amount,
                                const QString &icon,
                                AccountType::Type type);
    Q_INVOKABLE bool updateAccount(int id,
                               const qreal amount,
                               const QString &name,
                               const QString &currency,
                               const QString &icon,
                               AccountType::Type type);
    Q_INVOKABLE bool removeAccount(int id);

private:
    AccountsModel m_cashAccounts;
    AccountsModel m_cardAccounts;
    AccountsModel m_debtAccounts;
    AccountsModel m_savingsAccounts;

    IAccountManager* m_accountManager = nullptr;

    bool initAccountsModels();

    void addAccount(const QSharedPointer<Account> &account);
    void removeAccount(const QSharedPointer<Account> &account);

};

#endif // FULLACCOUNTSMODEL_H
