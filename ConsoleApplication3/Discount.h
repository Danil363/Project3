#ifndef DISCOUNT_H
#define DISCOUNT_H

class Discount {
private:
    double discountPercentage;

public:
    Discount(double discountPercentage);
    double applyDiscount(double price) const;
};

#endif // DISCOUNT_H
