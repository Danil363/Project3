#include "homeappliance.h"


HomeAppliance::HomeAppliance(const QString& name, const QString& imagePath, double price, const QString& warranty)
    : Product(name, imagePath, price), warranty(warranty) {}


HomeAppliance::HomeAppliance(const HomeAppliance& other)
    : Product(other), warranty(other.warranty) {}


HomeAppliance& HomeAppliance::operator=(const HomeAppliance& other) {
    if (this != &other) {
        Product::operator=(other);
        warranty = other.warranty;
    }
    return *this;
}
