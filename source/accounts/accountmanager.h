#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QSharedPointer>

#include "../datastorage/iaccount.h"
#include "iaccountmanager.h"

class AccountManager : public QObject, public IAccountManager
{
    Q_OBJECT

public:

    AccountManager(IAccount * dataStorage = nullptr);
    virtual ~AccountManager();

    virtual int addAccount(const QString &name,
                           const QString &currency,
                           const qreal amount,
                           const QString &icon,
                           AccountType::Type type) override;

    virtual bool removeAccount(int id) override;

    virtual const QList<QSharedPointer<Account>>& getAccounts() const override;
    virtual QSharedPointer<Account> getAccount(int id) const override;
    virtual int countAccounts() const override;

    virtual bool updateAccount(int id,
                               const qreal amount,
                               const QString &name,
                               const QString &currency,
                               const QString &icon,
                               AccountType::Type type) override;

    virtual bool addAmount(int id, qreal value) override;
    virtual bool subAmount(int id, qreal value) override;

    void init();

private:
    IAccount::AccountsList m_accounts;
    IAccount::AccountsHash m_hashAccounts;

    IAccount * m_dataStorage;

    bool updateAmount(Account *account, qreal amount);
};

#endif // ACCOUNTMANAGER_H
