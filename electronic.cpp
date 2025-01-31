#include "electronic.h"

Electronic::Electronic(const QString& name, const QString& imagePath, double price, const QString& operatingTime)
    : Product(name, imagePath, price), operatingTime(operatingTime) {}


Electronic::Electronic(const Electronic& other)
    : Product(other), operatingTime(other.operatingTime) {}

Electronic& Electronic::operator=(const Electronic& other) {
    if (this != &other) {
        Product::operator=(other);
        operatingTime = other.operatingTime;
    }
    return *this;
}
