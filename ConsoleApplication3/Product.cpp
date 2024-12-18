#include "Product.h"
#include <iostream>

// Конструктор
Product::Product(int id, std::string name, double price, int quantity, std::string description)
    : id(id), name(name), price(price), quantity(quantity), description(description) {}

// Методи доступу
std::string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }
std::string Product::getDescription() const { return description; }

// Зміна кількості товару
void Product::updateQuantity(int newQuantity) {
    quantity = newQuantity;
}

// Виведення інформації про товар
void Product::displayProductInfo() const {
    std::cout << "ID: " << id << ", Назва: " << name
        << ", Ціна: " << price << ", Кількість: " << quantity
        << ", Опис: " << description << std::endl;
}
