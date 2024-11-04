#include "Cart.h"
#include <iostream>
#include <iomanip> // для форматирования вывода

void Cart::addItem(std::unique_ptr<Product> product, int quantity) {
    items.emplace_back(std::move(product), quantity);
}

void Cart::removeItem(int index) {
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);
        std::cout << "Товар удален из корзины.\n";
    }
    else {
        std::cout << "Неверный индекс.\n";
    }
}

double Cart::calculateTotal() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item.first->getPrice() * item.second; // цена * количество
    }
    return total;
}

void Cart::displayCart() const {
    if (items.empty()) {
        std::cout << "Корзина пуста.\n";
        return;
    }

    std::cout << "Товары в корзине:\n";
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << ". " << items[i].first->getName()
            << " - " << items[i].second << " шт, "
            << "Цена за единицу: " << items[i].first->getPrice() << " грн\n";
    }
    std::cout << "Общая стоимость: " << std::fixed << std::setprecision(2) << calculateTotal() << " грн\n";
}

void Cart::clearCart() {
    items.clear();
    std::cout << "Корзина очищена.\n";
}
