#pragma once
#include <vector>
#include "admin.h"
#include "user.h"
#include <fstream>
#include <iostream>
#include <string>


class AdminUserManagement {
private: 
    Admin admin; // єдиний адмін
    std::vector<User>& users; // вектор користувачів
public:
    //  ініціалізація поля users за допомогою списку ініціалізації конструктора, тому що воно є посиланням. інакше виникне помилка компіляції.
    AdminUserManagement(std::vector<User>& users) : users(users) {}

    void view_all_users() { //  перегляд всіх користувачів
        std::cout << "====== Список всіх користувачів ======" << std::endl;
        if (users.empty()) {
            std::cout << "Список користувачів порожній" << std::endl;
            return;
        }

        for (size_t i = 0; i < users.size(); i++) {
            std::cout << "  Користувач №" << i + 1 << std::endl;
            std::cout << "ПІБ: " << users[i].get_full_name() << std::endl;
            std::cout << "Адреса: " << users[i].get_address() << std::endl;
            std::cout << "Телефон: " << users[i].get_phone() << std::endl;
            std::cout << "Логін: " << users[i].get_username() << std::endl;
            std::cout << "Пароль: " << users[i].get_password() << std::endl;
            std::cout << "--------------------------" << std::endl;
        }
    }

    void add_user() {   // додавання нового уористувача
        std::string name, address, phone, username, password, dashes;

        std::cout << "=== Додавання нового користувача ===" << std::endl;
        std::cout << "Введіть ПІБ: ";
        std::cin.ignore();
        std::getline(std::cin, name);

        std::cout << "Введіть адресу: ";
        std::getline(std::cin, address);

        std::cout << "Введіть телефон: ";
        std::getline(std::cin, phone);

        bool username_unique = false;
        while (!username_unique) {
            std::cout << "Введіть логін: ";
            std::getline(std::cin, username);

            username_unique = true;
            for (const User& user : users) {
                if (user.get_username() == username) {
                    std::cout << "Цей логін вже використовується. Оберіть інший, будь ласка" << std::endl;
                    username_unique = false;
                    break;
                }
            }
        }

        std::cout << "Введіть пароль: ";
        std::getline(std::cin, password);


        User new_user(name, address, phone, username, password);
        users.push_back(new_user);

        std::ofstream file(User::users_file, std::ios::app);  //збереження у файл
        if (file.is_open()) {
            file << name << std::endl;
            file << address << std::endl;
            file << phone << std::endl;
            file << username << std::endl;
            file << password << std::endl;
            file<<"--------------------------"<< std::endl;
            file.close();
        }

        std::cout << "Користувача успішно додано!" << std::endl;
    }

    void delete_user() { // видалення користувача
        if (users.empty()) {
            std::cout << "Список користувачів порожній." << std::endl;
            return;
        }

        view_all_users();
        int user_index;
        std::cout << "Введіть номер користувача для видалення: ";
        std::cin >> user_index;

        if (user_index >= 1 && user_index <= users.size()) {
            users.erase(users.begin() + user_index - 1); // видалення елемента з вектора users за певним індексом
            std::cout << "Користувача успішно видалено!" << std::endl;

            std::ofstream file(User::users_file);  //  оновлення файлу користувачів
            if (file.is_open()) {
                for (const User& user : users) {
                    file << user.get_full_name() << std::endl;
                    file << user.get_address() << std::endl;
                    file << user.get_phone() << std::endl;
                    file << user.get_username() << std::endl;
                    file << user.get_password() << std::endl;
                    file << "--------------------------" << std::endl;
                }
                file.close();
            }
        }
        else {
            std::cout << "Невірний номер користувача." << std::endl;
        }
    }
};