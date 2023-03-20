#include "datastorage.h"
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlError>
#include <QFile>
#include <QRegularExpression>
#include <QDebug>

int DataStorage::addTransaction(QSharedPointer<Transaction> &transaction)
{
    if(transaction.isNull() || !m_database.isOpen())
        return -1;

    QSqlQuery query(m_database);
    query.prepare("insert into transactions "
                  "(text,  account, amount, date, category, type) "
                  "VALUES(:1, :2, :3, :4, :5, :6);");

    query.bindValue(":1", transaction->m_text);
    query.bindValue(":2", transaction->m_account);
    query.bindValue(":3", transaction->m_cost);
    query.bindValue(":4", transaction->m_time.toString("dd.MM.yyyy hh:mm:ss"));
    query.bindValue(":5", transaction->m_category);
    query.bindValue(":6", transaction->m_isIncome);

    if(!query.exec())
        return -1;

    query.prepare("select MAX(id) as id from transactions");
    return (!query.exec() || !query.next()) ? -1 : query.value("id").toInt();
}

bool DataStorage::updateTransaction(int id, int category, int account,
                                    const QDateTime &date,
                                    const QString &text,
                                    const qreal &cost,
                                    bool isIncome)
{
    if(!m_database.isOpen())
        return false;

    QSqlQuery query(m_database);
    query.prepare("UPDATE transactions SET "
                  "category = :1, "
                  "date = :2, "
                  "type = :3, "
                  "amount = :4, "
                  "account = :5, "
                  "text = :6 "
                  "where id = :7");

    query.bindValue(":1", category);
    query.bindValue(":2", date.toString("dd.MM.yyyy hh:mm:ss"));
    query.bindValue(":3", isIncome);
    query.bindValue(":4", cost);
    query.bindValue(":5", account);
    query.bindValue(":6", text);
    query.bindValue(":7", id);

    return query.exec();
}

bool DataStorage::removeTransaction(int id)
{
    if(!m_database.isOpen())
        return false;

    QSqlQuery query(m_database);
    query.prepare("delete from transactions where id = :1");

    query.bindValue(":1", id);

    return query.exec();
}

QHash<int, QList<QSharedPointer<Transaction>>> DataStorage::getTransactions(const QDateTime &from,
                                                                            const QDateTime &to,
                                                                            QObject *parent)
{
    QHash<int, QList<QSharedPointer<Transaction>>> transactions;

    if(!m_database.isOpen())
        return transactions;

    QSqlQuery query(m_database);
    QString request = "select * from transactions where :1 <= date AND :2 >= date";
    query.prepare(request);

    query.bindValue(":1", from.toString("dd.MM.yyyy hh:mm:ss"));
    query.bindValue(":2", to.toString("dd.MM.yyyy hh:mm:ss"));

    if(!query.exec())
        return transactions;

    readTransactions(query, transactions, parent);

    return transactions;
}

QHash<int, QList<QSharedPointer<Transaction>>> DataStorage::getTransactions(const QDateTime &from,
                                                                            const QDateTime &to,
                                                                            bool isIncome,
                                                                            QObject *parent)
{
    QHash<int, QList<QSharedPointer<Transaction>>> transactions;

    if(!m_database.isOpen())
        return transactions;

    QSqlQuery query(m_database);
    QString request = "select * from transactions where :1 <= date AND :2 >= date AND type = :3";
    query.prepare(request);

    query.bindValue(":1", from.toString("dd.MM.yyyy hh:mm:ss"));
    query.bindValue(":2", to.toString("dd.MM.yyyy hh:mm:ss"));
    query.bindValue(":3", isIncome);

    if(!query.exec())
        return transactions;

    readTransactions(query, transactions, parent);

    return transactions;
}

bool DataStorage::readAccounts(QPair<AccountsList*, AccountsHash*> &accounts, QObject* parent)
{
    auto& list = accounts.first;
    auto& hash = accounts.second;

    if(!m_database.isOpen() || !list || !hash)
        return false;

    QSqlQuery query(m_database);
    query.prepare("select * from accounts");

    if(!query.exec())
        return false;

    while(query.next())
    {
        qreal amount = query.value("amount").toDouble();
        QString name = query.value("name").toString();
        QString currency = query.value("currency").toString();
        QString icon = query.value("icon").toString();
        int id = query.value("id").toInt();
        AccountType::Type type = static_cast<AccountType::Type>(query.value("type").toInt());

        QSharedPointer<Account> account(new Account(name, currency, amount, icon, type, parent));
        account->m_id = id;

        list->append(account);
        hash->insert(id, account);
    }

    return true;
}

bool DataStorage::addAccount(Account *account)
{
    if(!account || !m_database.isOpen())
        return false;

    QSqlQuery query(m_database);
    query.prepare("insert into accounts (name, amount, currency, type, icon) "
                  "VALUES(:1, :2, :3, :4, :5);");

    query.bindValue(":1", account->m_name);
    query.bindValue(":2", account->m_amount);
    query.bindValue(":3", account->m_currency);
    query.bindValue(":4", static_cast<int>(account->m_type));
    query.bindValue(":5", account->m_icon);



    return query.exec();
}

bool DataStorage::updateAccount(int id, const qreal amount, const QString &name, const QString &currency,
                                const QString &icon, AccountType::Type type)
{

    if(!m_database.isOpen())
        return false;

    QSqlQuery query(m_database);
    query.prepare("UPDATE accounts SET "
                  "name = :1, "
                  "amount = :2, "
                  "currency = :3, "
                  "icon = :4, "
                  "type = :5, "
                  "where id = :6");

    query.bindValue(":1", name);
    query.bindValue(":2", amount);
    query.bindValue(":3", currency);
    query.bindValue(":4", icon);
    query.bindValue(":5", static_cast<int>(type));
    query.bindValue(":6", id);

    return query.exec();
}

bool DataStorage::removeAccount(int id)
{
    if(!m_database.isOpen())
        return false;

    QSqlQuery query(m_database);
    query.prepare("delete from accounts WHERE id = :1");

    query.bindValue(":1", id);

    return query.exec();
}

bool DataStorage::updateAmount(int id, qreal amount)
{
    if(!m_database.isOpen())
        return false;

    QSqlQuery query(m_database);
    query.prepare("UPDATE accounts SET amount = :1 where id = :2");

    query.bindValue(":1", amount);
    query.bindValue(":2", id);

    return query.exec();
}

bool DataStorage::execScript()
{
    QFile file(BASE_SCRIPT);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error open script file";
        return false;
    }

    QString script = file.readAll();
    file.close();

    script.replace(QRegularExpression("[\\n|\\r|\\t]+"), " ");
    QStringList requests = script.split(';', QString::SkipEmptyParts);

    QSqlQuery query(m_database);
    foreach(const auto &request, requests)
    {
        query.prepare(request);
        if(!query.exec())
            return false;
    }
    return true;
}

void DataStorage::readTransactions(QSqlQuery &query, QHash<int, QList<QSharedPointer<Transaction> > > &transactions, QObject* parent)
{
    while(query.next())
    {
        QDateTime time = QDateTime::fromString(query.value("date").toString(), "dd.MM.yyyy hh:mm:ss");
        qreal amount = query.value("amount").toDouble();
        QString text = query.value("text").toString();
        bool type = query.value("type").toBool();
        int id = query.value("id").toInt();
        int account = query.value("account").toInt();
        int category = query.value("category").toInt();

        QSharedPointer<Transaction> transaction(new Transaction(category, account, time, text, amount, type, parent));
        transaction->m_id = id;

        transactions[id] << transaction;
    }
}

DataStorage::DataStorage() : m_database(QSqlDatabase::addDatabase("QSQLITE"))
{
    m_database.setDatabaseName(DATA_BASE);

    if(!m_database.open() || !execScript())
    {
        qDebug() << "Error open database";
        return;
    }

    QSqlQuery query(m_database);
    query.exec("PRAGMA foreign_keys = ON;");//without the request pragma don't active
}

DataStorage::~DataStorage()
{}
