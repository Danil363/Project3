#ifndef HOMEAPPLIANCE_H
#define HOMEAPPLIANCE_H

#include "product.h"

class HomeAppliance : public Product {
private:
    QString warranty;

public:
    HomeAppliance(const QString& name, const QString& imagePath, double price, const QString& warranty);
    HomeAppliance(const HomeAppliance& other);
    HomeAppliance& operator=(const HomeAppliance& other);
};

#endif // HOMEAPPLIANCE_H
