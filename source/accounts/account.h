#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QDateTime>
#include <QString>

class AccountType: public QObject
{
    Q_OBJECT

public:
    explicit AccountType(){}

    enum Type
    {
        NONE = 0,
        CASH,
        CARD,
        DEBT,
        SAVINGS
    };

    Q_ENUM(Type)
};

class Account : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id MEMBER id NOTIFY allChanged)
    Q_PROPERTY(qreal amount MEMBER amount NOTIFY amountChanged)
    Q_PROPERTY(QDateTime time MEMBER time NOTIFY timeChanged)
    Q_PROPERTY(QString name MEMBER name NOTIFY nameChanged)
    Q_PROPERTY(QString currency MEMBER currency NOTIFY currencyChanged)
    Q_PROPERTY(QString icon MEMBER icon NOTIFY iconChanged)
    Q_PROPERTY(QString color MEMBER color NOTIFY colorChanged)
    Q_PROPERTY(int type READ getType NOTIFY typeChanged)


public:
    explicit Account(QObject *parent = nullptr)
        :QObject(parent)
    {};

    virtual ~Account(){}

    QDateTime time;

    qreal amount = 0;

    QString name;
    QString currency;
    QString icon;
    QString color;

    int id = 0;

    AccountType::Type type;

    int getType() const {return type;}

signals:
    void timeChanged();
    void amountChanged();
    void nameChanged();
    void currencyChanged();
    void typeChanged();
    void iconChanged();
    void colorChanged();
    void allChanged();
};

#endif // ACCOUNT_H
