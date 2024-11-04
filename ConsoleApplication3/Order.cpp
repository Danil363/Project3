#include "Order.h"
#include <iostream>

Order::Order(int order_id, Customer* customer, std::vector<std::pair<std::unique_ptr<Product>, int>> items, double total_price)
    : order_id(order_id), customer(customer), total_price(total_price), status("Processing") {
    // Перемещаем содержимое items в члены класса
    this->items = std::move(items);
}

void Order::updateStatus(const std::string& new_status) {
    status = new_status;
    std::cout << "Статус заказа обновлен на: " << status << "\n";
}

void Order::displayOrderDetails() const {
    std::cout << "Детали заказа #" << order_id << ":\n";
    std::cout << "Клиент: " << customer->getUsername() << "\n";
    std::cout << "Статус: " << status << "\n";
    std::cout << "Товары:\n";
    for (const auto& item : items) {
        std::cout << "- " << item.first->getName() << " ("
            << item.second << " шт) - "
            << item.first->getPrice() << " грн за единицу\n";
    }
    std::cout << "Общая стоимость: " << total_price << " грн\n";
}

int Order::getOrderId() const {
    return order_id;
}

Customer* Order::getCustomer() const {
    return customer;
}

double Order::getTotalPrice() const {
    return total_price;
}

std::string Order::getStatus() const {
    return status;
}
