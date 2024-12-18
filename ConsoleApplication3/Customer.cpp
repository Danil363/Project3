#include "Customer.h"
#include "Cart.h"
#include <iostream>

Customer::Customer(int user_id, std::string username, std::string password)
    : User(user_id, username, password) {
    cart = new Cart();
}

void Customer::addToCart(Product& product, int quantity) {
    cart->addItem(product, quantity);
}

void Customer::viewCart() const {
    cart->displayCart();
}

void Customer::placeOrder() {
    std::cout << "Замовлення оформлено!" << std::endl;
    cart->clearCart();
}

Customer::~Customer() {
    delete cart;
}

