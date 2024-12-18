#ifndef ORDER_HISTORY_H
#define ORDER_HISTORY_H

#include "Order.h"
#include <vector>

class OrderHistory {
private:
    std::vector<Order> orders;

public:
    void addOrder(const Order& order);
    void displayHistory() const;
};

#endif // ORDER_HISTORY_H
