#pragma once
#include <string>
#include <iostream>

// примає масив з варіантами відповіді, їх кількість та варіант користувача
inline int ask_user(const int arr[], int size, std::string input) { // використання помилки для розгалужень (inline щоб не було помилки LNK2005) 
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
			std::cout << "Помилка: Такої відповіді немає" << std::endl;
			return -1;
		}
		else {
			std::cout << "Ваш вибір обробляється..." << std::endl;
			return num;
		}
	}
	catch (std::invalid_argument&) {
		std::cout << "Помилка: введіть цифру" << std::endl;
		return -1;
	}
	catch (const std::out_of_range&) {
		std::cout << "Помилка: введене число занадто велике або мале" << std::endl;
		return -1;
	}
}