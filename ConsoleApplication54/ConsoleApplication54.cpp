#include <iostream>
#include <windows.h>

#include "user_manager.h"
#include "user_menu.h"
#include "exception_function.h"
#include "admin_manager.h"
#include "admin_menu.h"
#include "test_info.h"

int main() {
    // щоб нормально читалась/записувалась інформація з/у файл на укр. мові
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    try {
        // Ініціалізація тестів перед входом в меню
        Test::start_program_get_all_test();

        std::string choice;
        int choices[] = { 1, 2, 3, 4 };
        UserManager user_manager;
        AdminManager admin_manager;

        while (true) {
            std::cout << "====== Головне меню ======" << std::endl;
            std::cout << "1 - Увійти в аккаунт користувача" << std::endl;
            std::cout << "2 - Увійти як адміністратор" << std::endl;
            std::cout << "3 - Зареєструватися" << std::endl;
            std::cout << "4 - Вихід" << std::endl;
            std::cout << "Ваш вибір: ";
            std::cin >> choice;
            int result = ask_user(choices, 4, choice);
            if (result == 1) {
                int user_index = user_manager.login_in_main();
                if (user_index >= 0) {
                    try {
                        User user = user_manager.get_user(user_index);
                        user_menu(user);
                    }
                    catch (const std::exception& e) {
                        std::cerr << "Помилка: " << e.what() << std::endl;
                    }
                }
            }
            else if (result == 2) { // вхід для адміна
                if (!admin_manager.check_admin()) {
                    std::cout << "Адміністратор ще не створений в системі. Створіть адміністратора:" << std::endl;
                    admin_manager.create_admin();
                }
                else {
                    if (admin_manager.login()) {
                        admin_menu(user_manager.get_users(), admin_manager);
                    }
                }
            }
            else if (result == 3) {
                User new_user = user_manager.register_new_user_in_main();
                user_menu(new_user);
            }
            else if (result == 4) {
                std::cout << "Дякуємо за використання програми! До побачення!" << std::endl;
                break;
            }
            else {
                std::cout << "Некоректний вибір. Спробуйте ще раз" << std::endl;
            }
        }
    }
    catch (...) {
        std::cerr << "Критична помилка. Перезапустіть програму" << std::endl;
    }
}