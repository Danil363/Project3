
#ifndef CART_H
#define CART_H

#include "Product.h"
#include <vector>

class Cart {
private:
    std::vector<std::pair<Product, int>> items;

public:
    void addItem(Product& product, int quantity);
    void removeItem(int index);
    double calculateTotal() const;
    void displayCart() const;
    void clearCart();
};

#endif
