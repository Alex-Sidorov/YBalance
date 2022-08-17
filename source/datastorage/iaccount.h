#ifndef IACCOUNT_H
#define IACCOUNT_H

#include <QList>
#include <QHash>
#include <QPair>
#include <QSharedPointer>

#include "../accounts/account.h"

class IAccount
{
public:

    virtual ~IAccount() {}

    virtual bool readAccounts(QPair< QList<QSharedPointer<Account>>*, QHash<int, QSharedPointer<Account>>*> &accounts) = 0;

    virtual bool addAccount(Account * account) = 0;
    virtual bool updateAccount(int id, const qreal amount, const QString &name, const QString &currency, const QString &icon, const QString &color, AccountType::Type type) = 0;
    virtual bool removeAccount(int id) = 0;

    virtual bool updateAmount(int id, qreal amount) = 0;
};

#endif // IACCOUNT_H
