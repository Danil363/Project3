#ifndef ELECTRONIC_H
#define ELECTRONIC_H

#include "product.h"

class Electronic : public Product {
private:
    QString operatingTime;

public:
    Electronic(const QString& name, const QString& imagePath, double price, const QString& operatingTime);
    Electronic(const Electronic& other);
    Electronic& operator=(const Electronic& other);
};

#endif // ELECTRONIC_H
