#ifndef IACCOUNT_H
#define IACCOUNT_H

#include <QList>
#include <QHash>
#include <QPair>
#include <QSharedPointer>
#include <QDateTime>

#include "../accounts/account.h"

class IAccount
{
public:

    using AccountsList = QList<QSharedPointer<Account>>;
    using AccountsHash = QHash<int, QSharedPointer<Account>>;

    virtual ~IAccount() {}

    virtual bool readAccounts(QPair< AccountsList*, AccountsHash*> &accounts, QObject* parent) = 0;

    virtual bool addAccount(Account * account) = 0;
    virtual bool updateAccount(int id, const qreal amount, const QString &name, const QString &currency,
                               const QString &icon, AccountType::Type type) = 0;
    virtual bool removeAccount(int id) = 0;

    virtual bool updateAmount(int id, qreal amount) = 0;
};

#endif // IACCOUNT_H
