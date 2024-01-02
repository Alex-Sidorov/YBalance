#ifndef ICATEGORIES_H
#define ICATEGORIES_H

#include "../categories/category.h"

class ICategories
{
public:

    using CategoryList = QList<QSharedPointer<Category>>;
    using CategoryHash = QHash<int, QSharedPointer<Category>>;

    virtual ~ICategories(){}

    virtual bool addCategory(const QSharedPointer<Category> &category) = 0;

    virtual bool removeCategory(const int id) = 0;

    virtual bool updateCategory(const int id, const QString &name, const QString &currency, const QString &icon, const bool isIncome) = 0;

    virtual void getCategories(QPair< CategoryList*, CategoryHash*> &categories, bool isIncome, QObject* parent = nullptr) = 0;

};

#endif // ICATEGORIES_H
