#include "product.h"


Product::Product(const QString& name, const QString& imagePath, double price)
    : name(name), imagePath(imagePath), price(price) {}

Product::Product() : name(""), imagePath(""), price(0.0) {}


Product::~Product() = default;


Product::Product(const Product& other)
    : name(other.name), imagePath(other.imagePath), price(other.price) {}

Product& Product::operator=(const Product& other) {
    if (this != &other) {
        name = other.name;
        imagePath = other.imagePath;
        price = other.price;
    }
    return *this;
}
