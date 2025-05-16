#pragma once
#include <vector>
#include "admin.h"
#include "user.h"
#include <fstream>
#include <iostream>
#include <string>


class AdminUserManagement {
private: 
    Admin admin; // ������ ����
    std::vector<User>& users; // ������ ������������
public:
    //  ����������� ���� users �� ��������� ������ ����������� ������������, ���� �� ���� � ����������. ������ ������� ������� ���������.
    AdminUserManagement(std::vector<User>& users) : users(users) {}

    void view_all_users() { //  �������� ��� ������������
        std::cout << "====== ������ ��� ������������ ======" << std::endl;
        if (users.empty()) {
            std::cout << "������ ������������ �������" << std::endl;
            return;
        }

        for (size_t i = 0; i < users.size(); i++) {
            std::cout << "  ���������� �" << i + 1 << std::endl;
            std::cout << "ϲ�: " << users[i].get_full_name() << std::endl;
            std::cout << "������: " << users[i].get_address() << std::endl;
            std::cout << "�������: " << users[i].get_phone() << std::endl;
            std::cout << "����: " << users[i].get_username() << std::endl;
            std::cout << "������: " << users[i].get_password() << std::endl;
            std::cout << "--------------------------" << std::endl;
        }
    }

    void add_user() {   // ��������� ������ �����������
        std::string name, address, phone, username, password, dashes;

        std::cout << "=== ��������� ������ ����������� ===" << std::endl;
        std::cout << "������ ϲ�: ";
        std::cin.ignore();
        std::getline(std::cin, name);

        std::cout << "������ ������: ";
        std::getline(std::cin, address);

        std::cout << "������ �������: ";
        std::getline(std::cin, phone);

        bool username_unique = false;
        while (!username_unique) {
            std::cout << "������ ����: ";
            std::getline(std::cin, username);

            username_unique = true;
            for (const User& user : users) {
                if (user.get_username() == username) {
                    std::cout << "��� ���� ��� ���������������. ������ �����, ���� �����" << std::endl;
                    username_unique = false;
                    break;
                }
            }
        }

        std::cout << "������ ������: ";
        std::getline(std::cin, password);


        User new_user(name, address, phone, username, password);
        users.push_back(new_user);

        std::ofstream file(User::users_file, std::ios::app);  //���������� � ����
        if (file.is_open()) {
            file << name << std::endl;
            file << address << std::endl;
            file << phone << std::endl;
            file << username << std::endl;
            file << password << std::endl;
            file<<"--------------------------"<< std::endl;
            file.close();
        }

        std::cout << "����������� ������ ������!" << std::endl;
    }

    void delete_user() { // ��������� �����������
        if (users.empty()) {
            std::cout << "������ ������������ �������." << std::endl;
            return;
        }

        view_all_users();
        int user_index;
        std::cout << "������ ����� ����������� ��� ���������: ";
        std::cin >> user_index;

        if (user_index >= 1 && user_index <= users.size()) {
            users.erase(users.begin() + user_index - 1); // ��������� �������� � ������� users �� ������ ��������
            std::cout << "����������� ������ ��������!" << std::endl;

            std::ofstream file(User::users_file);  //  ��������� ����� ������������
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
            std::cout << "������� ����� �����������." << std::endl;
        }
    }
};