
#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Product.h"
#include <vector>

class Admin : public User {
public:
    Admin(int user_id, std::string username, std::string password);

    void addProduct(std::vector<Product>& products, const Product& product);
    void updateProduct(Product& product, int newQuantity);
};

#endif
