#pragma once
#include <string>
#include <vector>
#include "user.h"
#include <iostream>
#include <fstream>

class UserManager {
private:
    std::vector<User> users_vector; // ������ ����� ��� ������������

public:
    UserManager() {
        get_users_from_file(); // ��� ������� ����'����� ������� ��� ������������ � �����
    }

    void get_users_from_file() { // ������������ ������������ � ����� ��� ������� ��������
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
                std::getline(file, dashes);  // ������ ������� "---"

                User user(name, address, phone, username, password);
                users_vector.push_back(user);
            }

            file.close();
            std::cout << "����������� " << users_vector.size() << " ������������ � �����." << std::endl;
        }
        else {
            std::cout << "���� ������������ �� ��������. ������� �����" << std::endl;
        }
    }

    bool save_user_to_file(const User& user) { // ���������� ����������� � ����
        std::ofstream file(User::users_file, std::ios::app); // �������� ����� ��� ������ � �����

        if (!file.is_open()) { // ���� �� ������� ������� ����
            return false;
        }

        // �������� � ����
        file << user.get_full_name() << std::endl;
        file << user.get_address() << std::endl;
        file << user.get_phone() << std::endl;
        file << user.get_username() << std::endl;
        file << user.get_password() << std::endl;
        file << "---------------------" << std::endl;

        file.close();
        return true;
    }

    int login(std::string username, std::string password) { //���� ����������� � ����������� (������� ������ ����������� � ������ ��� -1)
        for (size_t i = 0; i < users_vector.size(); i++) {
            if (users_vector[i].get_username() == username && users_vector[i].get_password() == password) {
                return i; // ������� ������ ����������� � ������
            }
        }
        return -1; //����������� �� ��������
    }

    int login_in_main() { //����� ��� ����� ��� ��������� (��� ������������ � main.cpp)
        std::string username, password;
        std::cout << "������ ����: ";
        std::cin >> username;
        std::cout << "������ ������: ";
        std::cin >> password;

        int result = login(username, password);

        if (result >= 0) {
            std::cout << "���� �������! ³����, " << users_vector[result].get_full_name() << "!" << std::endl;
        }
        else {
            std::cout << "������� ���� ��� ������. ��������� �� ���" << std::endl;
        }

        return result;
    }

       //��������� ������ ����������� (������� ��'��� ������ �����������)
    User register_new_user(std::string name, std::string address, std::string phone, std::string username, std::string password) {
        User new_user(name, address, phone, username, password); // ��������� ������ �����������
        users_vector.push_back(new_user); // ��������� ������ ����������� � ������
        save_user_to_file(new_user); // ���������� ������ ����������� � ����
        return new_user;
    }

    User register_new_user_in_main() {  // ����� ��� ��������� ��� ��������� (��� ������������ � main.cpp)
        std::string name, address, phone, username, password;

        std::cout << "===== ��������� =====" << std::endl;

        std::cout << "������ ��� ϲ�: " << std::endl;
        std::cin.ignore(); // ����� ����� ����� ����� �������� ����
        std::getline(std::cin, name); // ����� ����� ��� � ��������
        
        std::cout << "������ ���� ������� ������: " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, address);
        
        std::cout << "������ ��� ����� ��������: " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, phone);

        bool username_unique = false;
        do {
            std::cout << "������ ����: ";
            std::cin >> username;

            username_unique = username_is_unique(username);
            if (!username_unique) {
                std::cout << "���������� � ����� ������ ��� ����. ��������� ����� ����" << std::endl;
            }
        } while (!username_unique);

        std::cout << "������ ������: ";
        std::cin >> password;

        return register_new_user(name, address, phone, username, password);
    }

    bool username_is_unique(std::string username) {  // �������� ���� �� ����������
        for (size_t i = 0; i < users_vector.size(); i++) {
            if (users_vector[i].get_username() == username) {
                return false; // ���� ����������� � ����� ������ ��������
            }
        }
        return true; // ���� ���� ���������
    }

    User get_user(int index) {  //  ������� ����������� �� �������� ��������
        if (index >= 0 && index < users_vector.size()) {  // ���� ������ � � ������
            return users_vector[index];
        }
        else {
            std::cout << "������ ����������� ���� ������ �������" << std::endl;
        }
    }

    int get_user_count() { // ������� ������� ������������
        return users_vector.size();
    }

    std::vector<User>& get_users() {
        return users_vector;
    }
};