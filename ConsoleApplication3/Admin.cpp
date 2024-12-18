#include "Admin.h"
#include <iostream>

Admin::Admin(int user_id, std::string username, std::string password)
    : User(user_id, username, password) {}

void Admin::addProduct(std::vector<Product>& products, const Product& product) {
    products.push_back(product);
    std::cout << "Товар додано: " << product.getName() << std::endl;
}

void Admin::updateProduct(Product& product, int newQuantity) {
    product.updateQuantity(newQuantity);
    std::cout << "Кількість товару оновлено: " << product.getName() << " до " << newQuantity << std::endl;
}
