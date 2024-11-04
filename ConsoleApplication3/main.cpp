#include <iostream>
#include <vector>
#include "Product.h"
#include "Customer.h"
#include "Admin.h"
#include "HeapSort.h" 
#include "OrderHistory.h"
#include "Electronics.h"
#include "Clothing.h"
#include "Grocery.h"

int main() {
    std::vector<Order> orders;
    std::vector<User*> users;  // Зберігаємо користувачів
    OrderHistory orderHistory;

    std::vector<Product*> products;

    products.push_back(new Electronics("Телефон", 15000, 10, "Сучасний смартфон"));
    products.push_back(new Clothing("Футболка", 500, 50, "Котонова футболка"));
    products.push_back(new Grocery("Хліб", 30, 100, "Свіжий хліб"));

    heapSort(products);

    std::cout << "Товари, відсортовані за ціною:\n";
    for (const auto& product : products) {
        std::cout << product->getName() << " (" << product->getCategory() << ") - "
            << product->getPrice() << " грн\n";
    }

    for (auto product : products) {
        delete product;
    }

    // Реєстрація та авторизація
    std::string username, password;
    std::cout << "Введіть ім'я користувача для реєстрації: ";
    std::cin >> username;
    std::cout << "Введіть пароль: ";
    std::cin >> password;
    User::registerUser(users, username, password);

    std::cout << "Введіть ім'я користувача для авторизації: ";
    std::cin >> username;
    std::cout << "Введіть пароль: ";
    std::cin >> password;
    User* loggedInUser = User::loginUser(users, username, password);
    if (loggedInUser) {
        // Додаткові дії, якщо користувач увійшов
        // Додати логіку для покупця або адміністратора
    }
    return 0;
    }