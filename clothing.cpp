#include "clothing.h"

Clothing::Clothing(const QString& name, const QString& imagePath, double price, const QString& material, const QString& size)
    : Product(name, imagePath, price), material(material), size(size) {}

Clothing::Clothing(const Clothing& other)
    : Product(other), material(other.material), size(other.size) {}

Clothing& Clothing::operator=(const Clothing& other) {
    if (this != &other) {
        Product::operator=(other);
        material = other.material;
        size = other.size;
    }
    return *this;
}
