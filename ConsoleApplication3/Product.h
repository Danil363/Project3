
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int id;
    std::string name;
    double price;
    int quantity;
    std::string description;

public:
    Product(int id, std::string name, double price, int quantity, std::string description);

    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;
    std::string getDescription() const;

    void updateQuantity(int newQuantity);
    void displayProductInfo() const;
};

#endif