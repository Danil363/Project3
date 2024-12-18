#include "Cart.h"
#include <iostream>

void Cart::addItem(Product& product, int quantity) {
    items.push_back(std::make_pair(product, quantity));
}

void Cart::removeItem(int index) {
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);
    }
}

double Cart::calculateTotal() const {
    double total = 0;
    for (const auto& item : items) {
        total += item.first.getPrice() * item.second;
    }
    return total;
}

void Cart::displayCart() const {
    for (const auto& item : items) {
        std::cout << item.first.getName() << " x" << item.second
            << " = " << item.first.getPrice() * item.second << " грн" << std::endl;
    }
    std::cout << "Загальна вартість: " << calculateTotal() << " грн" << std::endl;
}

void Cart::clearCart() {
    items.clear();
}
