#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"

class Clothing : public Product {
private:
    QString material;
    QString size;

public:
    Clothing(const QString& name, const QString& imagePath, double price, const QString& material, const QString& size);
    Clothing(const Clothing& other);
    Clothing& operator=(const Clothing& other);
};

#endif // CLOTHING_H
