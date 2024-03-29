#ifndef IACCOUNTMANAGER_H
#define IACCOUNTMANAGER_H

#include "account.h"

class IAccountManager
{
public:

    virtual int addAccount(const QString &name,
                           const QString &currency,
                           const qreal amount,
                           const QString &icon,
                           AccountType::Type type) = 0;

    virtual bool removeAccount(int id) = 0;

    virtual const QList<QSharedPointer<Account>>& getAccounts() const = 0;
    virtual QSharedPointer<Account> getAccount(int id) const = 0;
    virtual int countAccounts() const = 0;

    virtual bool updateAccount(int id,
                               const qreal amount,
                               const QString &name,
                               const QString &currency,
                               const QString &icon,
                               AccountType::Type type) = 0;

    virtual bool addAmount(int id, qreal value) = 0;
    virtual bool subAmount(int id, qreal value) = 0;

    IAccountManager(){};
    virtual ~IAccountManager(){};
};

#endif // IACCOUNTMANAGER_H
