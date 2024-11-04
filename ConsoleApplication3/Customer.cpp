#include "Customer.h"
#include <iostream>

Customer::Customer(int user_id, const std::string& username, const std::string& password)
    : User(user_id, username, password), cart(std::make_unique<Cart>()) {}

// Метод для добавления товара в корзину
void Customer::addToCart(std::unique_ptr<Product> product, int quantity) {
    cart->addItem(std::move(product), quantity);
    std::cout << "Товар добавлен в корзину.\n";
}

// Метод для просмотра содержимого корзины
void Customer::viewCart() const {
    cart->displayCart();
}

// Метод для оформления заказа
void Customer::placeOrder() {
    if (cart->calculateTotal() > 0) {
        std::cout << "Заказ оформлен. Общая стоимость: " << cart->calculateTotal() << " грн\n";
        cart->clearCart(); // Очистка корзины после оформления заказа
    }
    else {
        std::cout << "Корзина пуста. Добавьте товары перед оформлением заказа.\n";
    }
}
