#include <iostream>
#include <vector>
#include "Product.h"
#include "Customer.h"
#include "Admin.h"

#include "OrderHistory.h"

int main() {
    std::vector<Product> products;
    std::vector<Order> orders;
    std::vector<User*> users;  // Зберігаємо користувачів
    OrderHistory orderHistory;

    // Завантажуємо дані з файлів


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