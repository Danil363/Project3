#ifndef FOOD_H
#define FOOD_H

#include "product.h"

class Food : public Product {
private:
    QString expirationDate;

public:
    Food(const QString& name, const QString& imagePath, double price, const QString& expirationDate);
    Food(const Food& other);
    Food& operator=(const Food& other);
};

#endif // FOOD_H
