#include "OrderHistory.h"
#include <iostream>

void OrderHistory::addOrder(const std::shared_ptr<Order>& order) {
    orders.push_back(order);
    std::cout << "Заказ #" << order->getOrderId() << " добавлен в историю.\n";
}

void OrderHistory::displayHistory() const {
    if (orders.empty()) {
        std::cout << "История заказов пуста.\n";
        return;
    }

    std::cout << "История заказов:\n";
    for (const auto& order : orders) {
        order->displayOrderDetails();
        std::cout << "----------------------\n";
    }
}
