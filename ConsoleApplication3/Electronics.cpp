#include "Electronics.h"

Electronics::Electronics(const std::string& name, double price, int quantity, const std::string& description)
    : Product(name, price, quantity, description) {}

std::string Electronics::getCategory() const {
    return "Електроніка";
}
