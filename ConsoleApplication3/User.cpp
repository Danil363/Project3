#include "User.h"
#include <iostream>
#include <vector>
#include <string>

User::User(int user_id, std::string username, std::string password)
    : user_id(user_id), username(username), password(password) {}

std::string User::getUsername() const {
    return username;
}

void User::login() {
    std::cout << "Вітаємо, " << username << "!" << std::endl;
}
bool User::registerUser(std::vector<User*>& users, std::string username, std::string password) {
    // Перевірка на унікальність імені
    for (const auto& user : users) {
        if (user->getUsername() == username) {
            std::cout << "Користувач з таким іменем вже існує." << std::endl;
            return false;
        }
    }
    // Реєстрація нового користувача
    users.push_back(new User(users.size() + 1, username, password));
    std::cout << "Користувача зареєстровано!" << std::endl;
    return true;
}

User* User::loginUser(const std::vector<User*>& users, std::string username, std::string password) {
    for (const auto& user : users) {
        if (user->getUsername() == username) {
            // Додати перевірку пароля
            return user;
        }
    }
    std::cout << "Неправильне ім'я користувача або пароль." << std::endl;
    return nullptr;
}
