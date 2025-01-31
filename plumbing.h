#ifndef PLUMBING_H
#define PLUMBING_H

#include "product.h"

class Plumbing : public Product {
private:
    QString material;

public:
    Plumbing(const QString& name, const QString& imagePath, double price, const QString& material);
    Plumbing(const Plumbing& other);
    Plumbing& operator=(const Plumbing& other);
};

#endif // PLUMBING_H
