#include "admin_menu.h"
#include "statistic_menu.h"
#include "admin_manage_users.h"
#include "admin_user_management.h"
#include "exception_function.h"
#include "test_result.h"
#include <iostream>

void admin_menu(std::vector<User>& users, AdminManager& admin_manager) {  // ������� �����
    AdminUserManagement user_management(users);
    TestResult res;
    std::string choice;
    int choices[] = { 1, 2, 3, 4, 5 };
    while (true) {
        std::cout << "====== ���� ������������ ======" << std::endl;
        std::cout << "1 - ������ ��� ������������" << std::endl;
        std::cout << "2 - ��������� �������������" << std::endl;
        std::cout << "3 - ����������� ����������" << std::endl;
        std::cout << "4 - ��������� �������" << std::endl;
        std::cout << "5 - �����" << std::endl;
        std::cout << "��� ����: ";
        std::cin >> choice;

        int result = ask_user(choices, 5, choice);
        switch (result) {
        case 1:
            admin_manager.change_admin_data();
            break;
        case 2:
            admin_manage_users(user_management);
            break;
        case 3:
            statistic_menu(res);
            break;
        case 4:
            admin_manage_tests();
            break;
        case 5:
            std::cout << "����� � ������ ������������..." << std::endl;
            return;
        }
    }
}