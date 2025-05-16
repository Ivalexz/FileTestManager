#pragma once
#include "admin.h"
#include <iostream>
#include <fstream>

class AdminManager { // клас, який відповідає за дії з даними адміна
private:
    Admin admin; // єдиний адмін
    bool is_admin = false; //по дефолту адміна немає

    static const std::string admins_file; // статична константа для назви файлу

    bool get_admin_from_file() {
        std::ifstream admin_file(admins_file);

        if (!admin_file.is_open()) {
            return false;  // якщо файл не вдалось відкрити
        }

        std::string username, password;
        std::getline(admin_file, username);//перший рядок файлу - унікальний логін
        std::getline(admin_file, password); // другий рядок - пароль до аккаунту адміна
        admin_file.close();

        if (username.empty() || password.empty()) { // якщо дані ще не внесено
            return false;
        }
         // якщо все ок і дані є, визначаємо адміна
        admin.set_username(username);
        admin.set_password(password);

        is_admin = true;
        return true;
    }

    bool save_admin_to_file() {  // зберігає адміна до файлу
        std::ofstream file(admins_file);
        if (!file.is_open()) {
            return false;
        }
        // записує інформацію в файл
        file << admin.get_username() << std::endl;
        file << admin.get_password() << std::endl;
        file.close();

        return true;
    }

public:
    AdminManager() {
        is_admin=get_admin_from_file(); // при запуску комп'ютера вигружає інфо про адміна з файлу, а якщо його немає просить створити
    }

    bool check_admin() { // перевірка, чи існує адмін
        return is_admin;
    }

    bool create_admin() { // створення адміна
        if (is_admin) {
            std::cout << "Адміністратор вже створений в системі" << std::endl;
            return false;
        }

        std::string username, password;

        std::cout << "=== Створення адміністратора ===" << std::endl;
        std::cout << "Введіть логін адміністратора: ";
        std::cin >> username;
        std::cout << "Введіть пароль адміністратора: ";
        std::cin >> password;

        admin.set_password(password);
        admin.set_username(username);

        if (save_admin_to_file()) { // якщо адміна успішно занесено до файду
            is_admin = true;
            std::cout << "Адміністратора успішно створено!" << std::endl;
            return true;
        }
        else {
            std::cout << "Помилка при створенні адміністратора" << std::endl;
            return false;
        }
    }

    bool login() { // вхід адмінв
        if (!is_admin) {
            std::cout << "Адміністратор не створений в системі." << std::endl;
            return false;
        }

        std::string input_username, input_password;
        std::cout << "=== Вхід адміністратора ===" << std::endl;
        std::cout << "Логін: ";
        std::cin >> input_username;
        std::cout << "Пароль: ";
        std::cin >> input_password;

        if (input_username == admin.get_username() && input_password == admin.get_password()) {
            std::cout << "Вхід успішний! Ви увійшли як адміністратор" << std::endl;
            return true;
        }
        else {
            std::cout << "Невірний логін або пароль адміністратора" << std::endl;
            return false;
        }
    }

    void change_admin_data() { // зміна даних адміна
        std::string new_username, new_password;
        std::cout << "=== Зміна даних адміністратора ===" << std::endl;
        std::cout << "Новий логін: ";
        std::cin >> new_username;

        std::cout << "Новий пароль: ";
        std::cin >> new_password;

        admin.set_username(new_username); // оновлює дані в об'єкті admin
        admin.set_password(new_password);

        std::ofstream file(admins_file); // оновлює файл
        if (file.is_open()) {
            file << new_username << std::endl;
            file << new_password << std::endl;
            file.close();
            std::cout << "Дані адміністратора успішно оновлено!" << std::endl;
        }
        else {
            std::cout << "Помилка при оновленні даних адміністратора" << std::endl;
        }
    }

};