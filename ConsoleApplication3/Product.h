
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    
    std::string name;
    double price;
    int quantity;
    std::string description;

public:
    Product( std::string name, double price, int quantity, std::string description);

    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;
    std::string getDescription() const;
    void setQuantity(int newQuantity);

    virtual ~Product() = default;

    virtual std::string getCategory() const = 0;

    void updateQuantity(int newQuantity);
    void displayProductInfo() const;
};

#endif