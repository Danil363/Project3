
#ifndef ORDER_H
#define ORDER_H

#include "Customer.h"
#include <vector>

class Order {
private:
    int order_id;
    Customer* customer;
    std::vector<std::pair<Product, int>> items;
    double total_price;
    std::string status;

   

public:
    Order(int order_id, Customer* customer, const std::vector<std::pair<Product, int>>& items, double total_price);
    void updateStatus(const std::string& new_status);
    void displayOrderDetails() const;
    int getOrderId() const;
    Customer* getCustomer() const;
    double getTotalPrice() const;
    std::string getStatus() const;
};

#endif

