#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>
#include <QDateTime>
#include <QString>

class Transaction : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal cost MEMBER cost NOTIFY costChanged)
    Q_PROPERTY(QDateTime time MEMBER cost NOTIFY timeChanged)
    Q_PROPERTY(QString account MEMBER cost NOTIFY accountChanged)
    Q_PROPERTY(QString currency MEMBER cost NOTIFY currencyChanged)
    Q_PROPERTY(QString text MEMBER cost NOTIFY textChanged)
    Q_PROPERTY(QString category MEMBER cost NOTIFY categoryChanged)

public:
    QDateTime time;

    qreal cost = 0;

    QString account;
    QString currency;
    QString text;
    QString category;

signals:
    void accountChanged();
    void timeChanged();
    void costChanged();
    void textChanged();
    void categoryChanged();
    void currencyChanged();
    void allChanged();
};

#endif // TRANSACTION_H
