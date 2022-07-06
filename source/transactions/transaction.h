#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>
#include <QDateTime>
#include <QString>

class Transaction : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id MEMBER id NOTIFY allChanged)
    Q_PROPERTY(qreal cost MEMBER cost NOTIFY costChanged)
    Q_PROPERTY(QDateTime time MEMBER time NOTIFY timeChanged)
    Q_PROPERTY(QString account MEMBER account NOTIFY accountChanged)
    Q_PROPERTY(QString text MEMBER text NOTIFY textChanged)
    Q_PROPERTY(QString category MEMBER category NOTIFY categoryChanged)
    Q_PROPERTY(bool isIncome MEMBER isIncome NOTIFY typeChanged)


public:
    explicit Transaction(QObject *parent = nullptr)
        :QObject(parent)
    {};
    virtual ~Transaction(){}

    QDateTime time;

    qreal cost = 0;

    QString account;
    QString text;
    QString category;

    int id = 0;

    bool isIncome = true;

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
