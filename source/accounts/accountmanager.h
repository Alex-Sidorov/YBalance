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
                           const QDateTime &date,
                           const QString &currency,
                           const qreal amount,
                           const QString &icon,
                           const QString &color,
                           AccountType::Type type) override;

    virtual bool removeAccount(int id) override;

    virtual QList<QSharedPointer<Account>> getAccounts() const override;
    virtual Account* getAccount(int id) const override;

    virtual bool updateAccount(int id,
                               const qreal amount,
                               const QString &name,
                               const QString &currency,
                               const QString &icon,
                               const QString &color,
                               AccountType::Type type) override;

    virtual bool addAmount(int id, qreal value) override;
    virtual bool subAmount(int id, qreal value) override;

private:
    IAccount::AccountsList m_accounts;
    IAccount::AccountsHash m_hashAccounts;

    IAccount * m_dataStorage;

    bool updateAmount(Account *account, qreal amount);
};

#endif // ACCOUNTMANAGER_H
