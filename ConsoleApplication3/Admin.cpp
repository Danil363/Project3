#include "Admin.h"
#include <iostream>

Admin::Admin(int user_id, const std::string& username, const std::string& password)
    : User(user_id, username, password) {}

// Метод для добавления товара в список
void Admin::addProduct(std::vector<std::unique_ptr<Product>>& products, std::unique_ptr<Product> product) {
    products.push_back(std::move(product));
    std::cout << "Товар успешно добавлен.\n";
}

// Метод для обновления количества товара
void Admin::updateProduct(Product* product, int newQuantity) {
    if (product) {
        product->setQuantity(newQuantity); // Предполагается, что в классе Product есть метод setQuantity
        std::cout << "Количество товара обновлено.\n";
    }
    else {
        std::cout << "Ошибка: товар не найден.\n";
    }
}
