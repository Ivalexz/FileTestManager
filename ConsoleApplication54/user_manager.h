#pragma once
#include <string>
#include <vector>
#include "user.h"
#include <iostream>
#include <fstream>

class UserManager {
private:
    std::vector<User> users_vector; // вектор даних про користувачів

public:
    UserManager() {
        get_users_from_file(); // при запуску комп'ютера вигружає усіх користувачів з файлу
    }

    void get_users_from_file() { // завантаження користувачів з файлу при запуску програми
        std::ifstream file(User::users_file);
        if (file.is_open()) {
            std::string name, address, phone, username, password, dashes;

            while (std::getline(file, name)) {
                if (name.empty()) {
                    continue;
                }

                std::getline(file, address);
                std::getline(file, phone);
                std::getline(file, username);
                std::getline(file, password);
                std::getline(file, dashes);  // читаємо рисочки "---"

                User user(name, address, phone, username, password);
                users_vector.push_back(user);
            }

            file.close();
            std::cout << "Завантажено " << users_vector.size() << " користувачів з файлу." << std::endl;
        }
        else {
            std::cout << "Файл користувачів не знайдено. Створюю новий" << std::endl;
        }
    }

    bool save_user_to_file(const User& user) { // збереження користувача у файл
        std::ofstream file(User::users_file, std::ios::app); // відкриття файлу для запису у кінець

        if (!file.is_open()) { // якщо не вдалось відкрити файл
            return false;
        }

        // дописуємо в файл
        file << user.get_full_name() << std::endl;
        file << user.get_address() << std::endl;
        file << user.get_phone() << std::endl;
        file << user.get_username() << std::endl;
        file << user.get_password() << std::endl;
        file << "---------------------" << std::endl;

        file.close();
        return true;
    }

    int login(std::string username, std::string password) { //вхід користувача з параметрами (повертає індекс користувача у векторі або -1)
        for (size_t i = 0; i < users_vector.size(); i++) {
            if (users_vector[i].get_username() == username && users_vector[i].get_password() == password) {
                return i; // повертає індекс користувача у векторі
            }
        }
        return -1; //користувача не знайдено
    }

    int login_in_main() { //метод для входу без параметрів (для використання в main.cpp)
        std::string username, password;
        std::cout << "Введіть логін: ";
        std::cin >> username;
        std::cout << "Введіть пароль: ";
        std::cin >> password;

        int result = login(username, password);

        if (result >= 0) {
            std::cout << "Вхід успішний! Вітаємо, " << users_vector[result].get_full_name() << "!" << std::endl;
        }
        else {
            std::cout << "Невірний логін або пароль. Спробуйте ще раз" << std::endl;
        }

        return result;
    }

       //реєстрація нового користувача (повертає об'єкт нового користувача)
    User register_new_user(std::string name, std::string address, std::string phone, std::string username, std::string password) {
        User new_user(name, address, phone, username, password); // створення нового користувача
        users_vector.push_back(new_user); // додавання нового користувача у вектор
        save_user_to_file(new_user); // збереження нового користувача у файл
        return new_user;
    }

    User register_new_user_in_main() {  // метод для реєстрації без параметрів (для використання в main.cpp)
        std::string name, address, phone, username, password;

        std::cout << "===== Реєстрація =====" << std::endl;

        std::cout << "Введіть своє ПІБ: " << std::endl;
        std::cin.ignore(); // очищає новий рядок перед читанням імені
        std::getline(std::cin, name); // зчитує цілий ввід з пробілами
        
        std::cout << "Введіть свою домашню адресу: " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, address);
        
        std::cout << "Введіть свій номер телефону: " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, phone);

        bool username_unique = false;
        do {
            std::cout << "Введіть логін: ";
            std::cin >> username;

            username_unique = username_is_unique(username);
            if (!username_unique) {
                std::cout << "Користувач з таким логіном вже існує. Спробуйте інший логін" << std::endl;
            }
        } while (!username_unique);

        std::cout << "Введіть пароль: ";
        std::cin >> password;

        return register_new_user(name, address, phone, username, password);
    }

    bool username_is_unique(std::string username) {  // перевіряє логін на унікальність
        for (size_t i = 0; i < users_vector.size(); i++) {
            if (users_vector[i].get_username() == username) {
                return false; // якщо користувача з таким логіном знайдено
            }
        }
        return true; // якщо логін унікальний
    }

    User get_user(int index) {  //  повертає користувача за вказаним індексом
        if (index >= 0 && index < users_vector.size()) {  // якщо індекс є у векторі
            return users_vector[index];
        }
        else {
            std::cout << "Індекс користувача поза межами вектора" << std::endl;
        }
    }

    int get_user_count() { // повертає кількість користувачів
        return users_vector.size();
    }

    std::vector<User>& get_users() {
        return users_vector;
    }
};