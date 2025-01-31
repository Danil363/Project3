#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product {
public:
    QString name;
    QString imagePath;
    double price;
    Product(const QString& name, const QString& imagePath, double price);
    Product();
    virtual ~Product();
    Product(const Product& other);
    Product& operator=(const Product& other);

};

#endif // PRODUCT_H
