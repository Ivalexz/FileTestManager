#pragma once
#include "admin.h"
#include <iostream>
#include <fstream>

class AdminManager { // ����, ���� ������� �� 䳿 � ������ �����
private:
    Admin admin; // ������ ����
    bool is_admin = false; //�� ������� ����� ����

    static const std::string admins_file; // �������� ��������� ��� ����� �����

    bool get_admin_from_file() {
        std::ifstream admin_file(admins_file);

        if (!admin_file.is_open()) {
            return false;  // ���� ���� �� ������� �������
        }

        std::string username, password;
        std::getline(admin_file, username);//������ ����� ����� - ��������� ����
        std::getline(admin_file, password); // ������ ����� - ������ �� �������� �����
        admin_file.close();

        if (username.empty() || password.empty()) { // ���� ��� �� �� �������
            return false;
        }
         // ���� ��� �� � ��� �, ��������� �����
        admin.set_username(username);
        admin.set_password(password);

        is_admin = true;
        return true;
    }

    bool save_admin_to_file() {  // ������ ����� �� �����
        std::ofstream file(admins_file);
        if (!file.is_open()) {
            return false;
        }
        // ������ ���������� � ����
        file << admin.get_username() << std::endl;
        file << admin.get_password() << std::endl;
        file.close();

        return true;
    }

public:
    AdminManager() {
        is_admin=get_admin_from_file(); // ��� ������� ����'����� ������� ���� ��� ����� � �����, � ���� ���� ���� ������� ��������
    }

    bool check_admin() { // ��������, �� ���� ����
        return is_admin;
    }

    bool create_admin() { // ��������� �����
        if (is_admin) {
            std::cout << "����������� ��� ��������� � ������" << std::endl;
            return false;
        }

        std::string username, password;

        std::cout << "=== ��������� ������������ ===" << std::endl;
        std::cout << "������ ���� ������������: ";
        std::cin >> username;
        std::cout << "������ ������ ������������: ";
        std::cin >> password;

        admin.set_password(password);
        admin.set_username(username);

        if (save_admin_to_file()) { // ���� ����� ������ �������� �� �����
            is_admin = true;
            std::cout << "������������ ������ ��������!" << std::endl;
            return true;
        }
        else {
            std::cout << "������� ��� �������� ������������" << std::endl;
            return false;
        }
    }

    bool login() { // ���� �����
        if (!is_admin) {
            std::cout << "����������� �� ��������� � ������." << std::endl;
            return false;
        }

        std::string input_username, input_password;
        std::cout << "=== ���� ������������ ===" << std::endl;
        std::cout << "����: ";
        std::cin >> input_username;
        std::cout << "������: ";
        std::cin >> input_password;

        if (input_username == admin.get_username() && input_password == admin.get_password()) {
            std::cout << "���� �������! �� ������ �� �����������" << std::endl;
            return true;
        }
        else {
            std::cout << "������� ���� ��� ������ ������������" << std::endl;
            return false;
        }
    }

    void change_admin_data() { // ���� ����� �����
        std::string new_username, new_password;
        std::cout << "=== ���� ����� ������������ ===" << std::endl;
        std::cout << "����� ����: ";
        std::cin >> new_username;

        std::cout << "����� ������: ";
        std::cin >> new_password;

        admin.set_username(new_username); // ������� ��� � ��'��� admin
        admin.set_password(new_password);

        std::ofstream file(admins_file); // ������� ����
        if (file.is_open()) {
            file << new_username << std::endl;
            file << new_password << std::endl;
            file.close();
            std::cout << "��� ������������ ������ ��������!" << std::endl;
        }
        else {
            std::cout << "������� ��� �������� ����� ������������" << std::endl;
        }
    }

};