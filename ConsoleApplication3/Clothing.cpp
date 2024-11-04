#include "Clothing.h"

Clothing::Clothing(const std::string& name, double price, int quantity, const std::string& description)
    : Product(name, price, quantity, description) {}

std::string Clothing::getCategory() const {
    return "Одяг";
}
