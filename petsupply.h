#ifndef PETSUPPLY_H
#define PETSUPPLY_H

#include "product.h"

class PetSupply : public Product {
private:
    QString animalType;

public:
    PetSupply(const QString& name, const QString& imagePath, double price, const QString& animalType);
    PetSupply(const PetSupply& other);
    PetSupply& operator=(const PetSupply& other);
};

#endif // PETSUPPLY_H
