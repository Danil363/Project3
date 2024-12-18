#include "Order.h"
#include <iostream>

Order::Order(int order_id, Customer* customer, const std::vector<std::pair<Product, int>>& items, double total_price)
    : order_id(order_id), customer(customer), items(items), total_price(total_price), status("Обробляється") {}

void Order::updateStatus(const std::string& new_status) {
    status = new_status;
}

void Order::displayOrderDetails() const {
    std::cout << "Номер замовлення: " << order_id << std::endl;
    std::cout << "Покупець: " << customer->getUsername() << std::endl;
    for (const auto& item : items) {
        std::cout << item.first.getName() << " x" << item.second
            << " = " << item.first.getPrice() * item.second << " грн" << std::endl;
    }
    std::cout << "Загальна вартість: " << total_price << " грн" << std::endl;
    std::cout << "Статус: " << status << std::endl;
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
