#ifndef ICATEGORIESMANAGER_H
#define ICATEGORIESMANAGER_H

#include <QString>
#include "category.h"

class ICategoriesManager {

public:
    virtual ~ICategoriesManager(){}

    virtual bool updateCategory(const int id, const QString &name, const QString &currency, const QString &icon, const bool isIncome) = 0;
    virtual bool addCategory(const QString &name, const QString &currency, const QString &icon, const bool isIncome) = 0;
    virtual bool removeCategory(const int id) = 0;
    virtual QSharedPointer<Category> getCategory(int id) = 0;
    virtual QList<QSharedPointer<Category>> getCategories(bool isIncome) = 0;
};

#endif // ICATEGORIESMANAGER_H
