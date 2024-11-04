#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Product.h"
#include <vector>
#include <memory> // для использования std::unique_ptr

class Admin : public User {
public:
    Admin(int user_id, const std::string& username, const std::string& password);

    // Метод для добавления товара
    void addProduct(std::vector<std::unique_ptr<Product>>& products, std::unique_ptr<Product> product);

    // Метод для обновления количества товара
    void updateProduct(Product* product, int newQuantity);
};

#endif // ADMIN_H
