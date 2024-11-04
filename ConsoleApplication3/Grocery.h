#ifndef GROCERY_H
#define GROCERY_H

#include "Product.h"

class Grocery : public Product {
public:

    Grocery(const std::string& name, double price, int quantity, const std::string& description);

    std::string getCategory() const override;
};

#endif // GROCERY_H
