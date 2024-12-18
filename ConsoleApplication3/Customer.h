
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "Cart.h"

class Customer : public User {
private:
    Cart* cart;

public:
    Customer(int user_id, std::string username, std::string password);
    void addToCart(Product& product, int quantity);
    void viewCart() const;
    void placeOrder();

    ~Customer();
};

#endif
