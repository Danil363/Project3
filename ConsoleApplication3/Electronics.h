#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "Product.h"

class Electronics : public Product {
public:
    Electronics(const std::string& name, double price, int quantity, const std::string& description);

    std::string getCategory() const override;
};

#endif // ELECTRONICS_H
