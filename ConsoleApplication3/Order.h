#ifndef ORDER_H
#define ORDER_H

#include "Customer.h"
#include "Product.h"
#include <vector>
#include <memory>
#include <string>

class Order {
private:
    int order_id;
    Customer* customer;  // Заказчик
    std::vector<std::pair<std::unique_ptr<Product>, int>> items;  // Пары "товар и количество"
    double total_price;
    std::string status;

public:
    // Конструктор принимает список товаров как вектор пар с уникальными указателями
    Order(int order_id, Customer* customer, std::vector<std::pair<std::unique_ptr<Product>, int>> items, double total_price);

    // Метод для обновления статуса заказа
    void updateStatus(const std::string& new_status);

    // Метод для отображения деталей заказа
    void displayOrderDetails() const;

    // Геттеры
    int getOrderId() const;
    Customer* getCustomer() const;
    double getTotalPrice() const;
    std::string getStatus() const;
};

#endif // ORDER_H
