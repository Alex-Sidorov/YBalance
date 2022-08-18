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

    Q_PROPERTY(int id MEMBER m_id NOTIFY allChanged)
    Q_PROPERTY(qreal amount MEMBER m_amount NOTIFY amountChanged)
    Q_PROPERTY(QDateTime time MEMBER m_time NOTIFY timeChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString currency MEMBER m_currency NOTIFY currencyChanged)
    Q_PROPERTY(QString icon MEMBER m_icon NOTIFY iconChanged)
    Q_PROPERTY(QString color MEMBER m_color NOTIFY colorChanged)
    Q_PROPERTY(int type READ getType NOTIFY typeChanged)


public:
    explicit Account(QObject *parent = nullptr)
        :QObject(parent)
    {};

    Account(const QString &name,
            const QDateTime &date,
            const QString &currency,
            const qreal amount,
            const QString &icon,
            const QString &color,
            AccountType::Type type,
            QObject *parent = nullptr)
        :QObject(parent),
        m_time(date),
        m_amount(amount),
        m_name(name),
        m_currency(currency),
        m_icon(icon),
        m_color(color),
        m_type(type)
        {};

    virtual ~Account(){}

    QDateTime m_time;

    qreal m_amount = 0;

    QString m_name;
    QString m_currency;
    QString m_icon;
    QString m_color;

    int m_id = 0;

    AccountType::Type m_type;

    int getType() const {return m_type;}

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
