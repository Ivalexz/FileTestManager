#pragma once
#include <iostream>
#include <string>
#include "exception_function.h"

class Question { // ���� ��� ������ ��������� �� ������� ������ �����������
private:
	std::string question_text; // ����� ���������
	std::string answers_arr[4]; // ����� ��������
	int correct_answer_index; // ������ ��������� ������ (0-3)
	int current_question; // ����� ��������� ���������
public:
	explicit Question(std::string question_text, std::string answers[4], int correct_answer_index, int current_questtion) {
		this->question_text = question_text;
		for (int i = 0; i < 4; i++) {
			this->answers_arr[i] = answers[i];
		}
		this->correct_answer_index = correct_answer_index;
		this->current_question = current_questtion;
	}
	int ask() { // �������� ������� ����������� �� ���������  1 - ���������, 0 - �����������, -1 - �����
		int choices[5] = {0, 1,2,3,4}; // ������� ������ (0 ��� ������)
		std::string users_answer;
		bool answered = false;
		while (!answered) // ���� ���� ������, ������� ������������
		{
			std::cout << current_question<<") "<< question_text << std::endl; // ���� ���������
			for (size_t i = 0; i < 4; i++)
			{
				std::cout << "  " << i + 1 << ") " << answers_arr[i] << std::endl; // ���� ������� ������
			}
			std::cout << "���� ������� (1, 2, 3, 4 ��� 0 - �����): ";
			std::cin >> users_answer;

			if (users_answer == "0") {
				return -1; // �����
			}

			int result = ask_user(choices, 5, users_answer); // �������� ����������
			std::cout << std::endl;
			if (result != -1) {
				answered = true;
				if (result - 1 == correct_answer_index) {
					return 1; // ���������
				}
				else {
					return 0; // �����������
				}
			}
		}
		return 0; // �� �������� ������, ���� ���� ��� �� ���
	}

	std::string get_question_text() const {
		return question_text;
	}

	std::string get_answer(int index) const {
		if (index >= 0 && index < 4) {
			return answers_arr[index];
		}
		return "";
	}

	int get_correct_answer_index() const {
		return correct_answer_index;
	}

	std::string get_correct_answer() const {
		return answers_arr[correct_answer_index];
	}
};