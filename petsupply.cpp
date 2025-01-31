#include "petsupply.h"

PetSupply::PetSupply(const QString& name, const QString& imagePath, double price, const QString& animalType)
    : Product(name, imagePath, price), animalType(animalType) {}

PetSupply::PetSupply(const PetSupply& other)
    : Product(other), animalType(other.animalType) {}

PetSupply& PetSupply::operator=(const PetSupply& other) {
    if (this != &other) {
        Product::operator=(other);
        animalType = other.animalType;
    }
    return *this;
}
