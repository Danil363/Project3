#include "plumbing.h"

Plumbing::Plumbing(const QString& name, const QString& imagePath, double price, const QString& material)
    : Product(name, imagePath, price), material(material) {}


Plumbing::Plumbing(const Plumbing& other)
    : Product(other), material(other.material) {}

Plumbing& Plumbing::operator=(const Plumbing& other) {
    if (this != &other) {
        Product::operator=(other);
        material = other.material;
    }
    return *this;
}
