#include "Discount.h"

Discount::Discount(double discountPercentage) : discountPercentage(discountPercentage) {}

double Discount::applyDiscount(double price) const {
    return price * (1 - discountPercentage / 100);
}
