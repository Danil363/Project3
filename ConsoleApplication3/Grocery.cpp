#include "Grocery.h"

Grocery::Grocery(const std::string& name, double price, int quantity, const std::string& description)
    : Product(name, price, quantity, description) {}

std::string Grocery::getCategory() const {
    return "Продукти";
}
