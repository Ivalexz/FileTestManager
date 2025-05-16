#pragma once
#include <string>
#include <iostream>

// ����� ����� � ��������� ������, �� ������� �� ������ �����������
inline int ask_user(const int arr[], int size, std::string input) { // ������������ ������� ��� ����������� (inline ��� �� ���� ������� LNK2005) 
	try {
		int num = std::stoi(input);
		bool true_choice = false;

		for (size_t i = 0; i < size; i++) {
			if (num == arr[i]) {
				true_choice = true;
				break;
			}
		}

		if (!true_choice) {
			std::cout << "�������: ���� ������ ����" << std::endl;
			return -1;
		}
		else {
			std::cout << "��� ���� ������������..." << std::endl;
			return num;
		}
	}
	catch (std::invalid_argument&) {
		std::cout << "�������: ������ �����" << std::endl;
		return -1;
	}
	catch (const std::out_of_range&) {
		std::cout << "�������: ������� ����� ������� ������ ��� ����" << std::endl;
		return -1;
	}
}