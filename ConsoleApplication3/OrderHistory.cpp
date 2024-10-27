#include "OrderHistory.h"
#include <iostream>

void OrderHistory::addOrder(const Order& order) {
    orders.push_back(order);
}

void OrderHistory::displayHistory() const {
    std::cout << "Історія замовлень:" << std::endl;
    for (const auto& order : orders) {
        order.displayOrderDetails();
        std::cout << std::endl; // Розділення між замовленнями
    }
}
