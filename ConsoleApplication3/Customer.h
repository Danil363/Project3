#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "Cart.h"
#include <memory>

class Customer : public User {
private:
    std::unique_ptr<Cart> cart;

public:
    Customer(int user_id, const std::string& username, const std::string& password);

    // Метод для добавления товара в корзину
    void addToCart(std::unique_ptr<Product> product, int quantity);

    // Метод для просмотра содержимого корзины
    void viewCart() const;

    // Метод для оформления заказа
    void placeOrder();
};

#endif // CUSTOMER_H
