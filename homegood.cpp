#include "homegood.h"


HomeGood::HomeGood(const QString& name, const QString& imagePath, double price, double weight, const QString& size)
    : Product(name, imagePath, price), weight(weight), size(size) {}


HomeGood::HomeGood(const HomeGood& other)
    : Product(other), weight(other.weight), size(other.size) {}


HomeGood& HomeGood::operator=(const HomeGood& other) {
    if (this != &other) {
        Product::operator=(other);
        weight = other.weight;
        size = other.size;
    }
    return *this;
}
