#ifndef CLOTHING_H
#define CLOTHING_H

#include "Product.h"

class Clothing : public Product {
public:
    Clothing(const std::string& name, double price, int quantity, const std::string& description);

    std::string getCategory() const override;
};

#endif // CLOTHING_H
