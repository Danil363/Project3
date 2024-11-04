#ifndef ORDER_HISTORY_H
#define ORDER_HISTORY_H

#include "Order.h"
#include <vector>
#include <memory>

class OrderHistory {
private:
    std::vector<std::shared_ptr<Order>> orders; // Вектор умных указателей на заказы

public:
    void addOrder(const std::shared_ptr<Order>& order); // Добавление заказа
    void displayHistory() const; // Отображение истории заказов
};

#endif // ORDER_HISTORY_H
