#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>
#include <QDateTime>
#include <QString>

class Transaction : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id MEMBER m_id NOTIFY allChanged)
    Q_PROPERTY(qreal cost MEMBER m_cost NOTIFY costChanged)
    Q_PROPERTY(QDateTime time MEMBER m_time NOTIFY timeChanged)
    Q_PROPERTY(int account MEMBER m_account NOTIFY accountChanged)
    Q_PROPERTY(QString text MEMBER m_text NOTIFY textChanged)
    Q_PROPERTY(int category MEMBER m_category NOTIFY categoryChanged)
    Q_PROPERTY(bool isIncome MEMBER m_isIncome NOTIFY typeChanged)


public:
    explicit Transaction(QObject *parent = nullptr)
        :QObject(parent)
    {};

    Transaction(const int category,
                const int account,
                const QDateTime &date,
                const QString &text,
                const qreal &cost,
                bool isIncome,
                QObject *parent = nullptr)
        :QObject(parent),
        m_time(date),
        m_text(text),
        m_cost(cost),
        m_account(account),
        m_category(category),
        m_isIncome(isIncome)
        {};

    virtual ~Transaction(){}

    QDateTime m_time;

    QString m_text;

    qreal m_cost = 0;

    int m_account;
    int m_category;

    int m_id = 0;

    bool m_isIncome = true;

signals:
    void accountChanged();
    void timeChanged();
    void costChanged();
    void textChanged();
    void categoryChanged();
    void typeChanged();
    void allChanged();
};

#endif // TRANSACTION_H
