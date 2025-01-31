#include "food.h"


Food::Food(const QString& name, const QString& imagePath, double price, const QString& expirationDate)
    : Product(name, imagePath, price), expirationDate(expirationDate) {}


Food::Food(const Food& other) : Product(other), expirationDate(other.expirationDate) {}

Food& Food::operator=(const Food& other) {
    if (this != &other) {
        Product::operator=(other);
        expirationDate = other.expirationDate;
    }
    return *this;
}
