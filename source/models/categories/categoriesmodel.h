#ifndef CATEGORIESMODEL_H
#define CATEGORIESMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include "../../categories/category.h"

class CategoriesModel : public QAbstractListModel
{
    Q_OBJECT

    enum {
        idRole,
        nameRole,
        currencyRole,
        isIncome,
        iconRole
    };

public:
    explicit CategoriesModel(QObject *parent = nullptr);
    virtual ~CategoriesModel(){}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    QList<QSharedPointer<Category>> m_categories;
    QHash<int, QByteArray> m_roleNames;

    void initRoleNames();
};

#endif // CATEGORIESMODEL_H
