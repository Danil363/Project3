#ifndef HOMEGOOD_H
#define HOMEGOOD_H

#include "product.h"

class HomeGood : public Product {
private:
    double weight;
    QString size;

public:
    HomeGood(const QString& name, const QString& imagePath, double price, double weight, const QString& size);
    HomeGood(const HomeGood& other);
    HomeGood& operator=(const HomeGood& other);
};

#endif // HOMEGOOD_H
