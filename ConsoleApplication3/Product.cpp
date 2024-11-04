#include "Product.h"
#include <iostream>


// Конструктор
Product::Product( std::string name, double price, int quantity, std::string description )
    :  name(name), price(price), quantity(quantity), description(description) {}

// Методи доступу
std::string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }
std::string Product::getDescription() const { return description; }

// Зміна кількості товару
void Product::updateQuantity(int newQuantity) {
    quantity = newQuantity;
}

void Product::setQuantity(int newQuantity) {
    quantity = newQuantity;
}

// Виведення інформації про товар
void Product::displayProductInfo() const {
    std::cout <<  " Назва: " << name
        << ", Ціна: " << price << ", Кількість: " << quantity
        << ", Опис: " << description << std::endl;
}
