#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>
#include <QString>

class Category : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id MEMBER m_id NOTIFY allChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString currency MEMBER m_currency NOTIFY currencyChanged)
    Q_PROPERTY(QString icon MEMBER m_icon NOTIFY iconChanged)
    Q_PROPERTY(bool isIncome MEMBER m_isIncome NOTIFY typeChanged)

public:
    explicit Category(QObject *parent = nullptr)
        :QObject(parent)
        {};

    Category(const QString &name,
            const QString &currency,
            const QString &icon,
            const bool isIncome,
            QObject *parent = nullptr)
        :QObject(parent),
        m_name(name),
        m_icon(icon),
        m_currency(currency),
        m_isIncome(isIncome)
        {};

    virtual ~Category(){}

    QString m_name;
    QString m_icon;

    QString m_currency;

    int m_id = 0;

    bool m_isIncome = false;

signals:
    void nameChanged();
    void currencyChanged();
    void typeChanged();
    void iconChanged();
    void allChanged();
};


#endif // CATEGORY_H
