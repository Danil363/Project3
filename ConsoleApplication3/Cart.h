#ifndef CART_H
#define CART_H

#include "Product.h"
#include <vector>
#include <memory> // для std::unique_ptr

class Cart {
private:
    std::vector<std::pair<std::unique_ptr<Product>, int>> items; // пара: товар и его количество

public:
    void addItem(std::unique_ptr<Product> product, int quantity);
    void removeItem(int index);
    double calculateTotal() const;
    void displayCart() const;
    void clearCart();
};

#endif // CART_H
