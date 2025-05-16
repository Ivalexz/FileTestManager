#include "admin_manage_users.h"
#include <iostream>
#include "exception_function.h"

bool admin_manage_users(AdminUserManagement& admin_manager) { // ���� ��� ��������� ������������� (������������� ������)
    std::string choice;
    int choices[] = { 1, 2, 3, 4 };

    while (true) {
        std::cout << "====== ��������� ������������� ======" << std::endl;
        std::cout << "1 - �������� �����������" << std::endl;
        std::cout << "2 - �������� �����������" << std::endl;
        std::cout << "3 - ����������� ��� ������������" << std::endl;
        std::cout << "4 - �����" << std::endl;
        std::cout << "��� ����: ";
        std::cin >> choice;

        int result = ask_user(choices, 4, choice);

        if (result == 1) {
            admin_manager.add_user();
        }
        else if (result == 2) {
            admin_manager.delete_user();
        }
        else if (result == 3) {
            admin_manager.view_all_users();
        }
        else {
            break;
        }
    }

    return true;
}
