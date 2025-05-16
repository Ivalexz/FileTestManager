#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "question.h"
#include "exception_function.h"
#include "test_info.h"
#include "test_result.h"
#include "test_progress.h"

class Test { // ���� ��� ��������� ������� ����� ���������
private:
	TestResult* result; // ��������� ����� � ����� TestResult
	std::string test_name; // ����� �����
	std::string subject_name; // ����� ��������
	int subject_index; // ������ ��������
	int test_index; // ������ ����� ����� � �������
	int correct_answers; // ������� ���������� ��������
	int total_questions; // �������� ������� �������� � ����� ����
	bool is_completed; // �� ��������� ����
	int last_answered_question; // ����� ���������� ����������� ��������� (��� �����������)
	std::string username; // ���� ����������� ��� ���������� �������� � ����
	
	static const std::string test_file_name; // ���������� ����� ����� ��� ���������� �����
	static TestInfo test_info; // ��������� ��'��� ��� ������� �� ���������� ��� �����

public:
	explicit Test() {
		subject_index = -1;
		test_index = -1;
		correct_answers = 0;
		total_questions = 0;
		is_completed = false;
		last_answered_question = 0;
		username = "";
		subject_name = "";
		test_name = "";
	}

	explicit Test(int subject_index, int test_index) {
		this->subject_index = subject_index;
		this->test_index = test_index;
		this->correct_answers = 0;
		this->is_completed = false;
		this->last_answered_question = 0;
		this->username = "";

		if (subject_index >= 0 && subject_index < test_info.subjects.size() && test_index >= 0 && test_index < test_info.subjects[subject_index].tests.size()) {
			this->subject_name = test_info.subjects[subject_index].name;
			this->test_name = test_info.subjects[subject_index].tests[test_index].test_name;
			this->total_questions = test_info.subjects[subject_index].tests[test_index].questions.size();
		}
		else {
			this->subject_name = "�������� �������";
			this->test_name = "�������� ����";
			this->total_questions = 0;
		}
	}
	// ����������� ��� ������ � ��������� � ���������
	explicit Test(int subject_index, int test_index, int correct_answers, int last_answered_question, std::string username) {
		this->subject_index = subject_index;
		this->test_index = test_index;
		this->correct_answers = correct_answers;
		this->is_completed = false;
		this->last_answered_question = last_answered_question;
		this->username = username;

		if (subject_index >= 0 && subject_index < test_info.subjects.size() && test_index >= 0 && test_index < test_info.subjects[subject_index].tests.size()) {
			this->subject_name = test_info.subjects[subject_index].name;
			this->test_name = test_info.subjects[subject_index].tests[test_index].test_name;
			this->total_questions = test_info.subjects[subject_index].tests[test_index].questions.size();
		}
		else {
			this->subject_name = "�������� �������";
			this->test_name = "�������� ����";
			this->total_questions = 0;
		}
	}

	static void start_program_get_all_test() {// ��� ������� �������� ������� �� �����
		test_info.get_all_default_questions(); //��������� ������� �������

		try {  // ����� ����������� � ����� (���� ���� �)
			std::vector<TestInfo::TestStruct> taken_tests = test_info.get_tests_from_file(test_file_name);
			if (taken_tests.empty()) {
				throw 404;
			}
			else {
				std::cout << "����� ������ ���������� � �����" << std::endl;
			}
		}
		catch (...) {
			std::cout << "������� ��� ����������� ����� � �����" << std::endl;
			std::cout << "���������������� ������� �����" << std::endl;

			test_info.save_tests_to_file(test_file_name); //������ ������� ����� � ���� ��� ������������ ����
		}
	}

	static std::vector<std::string> get_subject_list() { // ������ ��� ��������� ������(�������) ��������
		std::vector<std::string> subject_names;
		for (const auto& subject : test_info.subjects) {
			subject_names.push_back(subject.name);
		}
		return subject_names;
	}

	static std::vector<std::string> get_test_list(int subject_index) { // ������ ��� ��������� ������(�������) �����
		std::vector<std::string> test_names;
		if (subject_index >= 0 && subject_index < test_info.subjects.size()) {// �� ��������� ������
			for (const auto& test : test_info.subjects[subject_index].tests) {
				test_names.push_back(test.test_name);
			}
		}
		return test_names;
	}

	void set_username(const std::string username) {  // ����������� ����� ����������� ��� ��������
		this->username = username;
	}

	bool run() {
		if (subject_index < 0 || test_index < 0 || subject_index >= test_info.subjects.size() || test_index >= test_info.subjects[subject_index].tests.size()) {
			std::cout << "�������: ������ ����� �����" << std::endl;
			return false;
		}
		std::cout << "�������ֲ�: ���� ������� ��������� � ���� ����� ��������� ������� ������� � ��������� ������"<<std::endl<<"�������: 1 (����� �������)" << std::endl<<"�������� '0' ��� ������" << std::endl << "��ϲղ�!" << std::endl;
		std::cout << "===== ����: " << test_name << "=====" << std::endl;

		 // ���� ���������� ����������� �� ������������ �����
		if (last_answered_question > 0) {
			std::cout << "����������� ����� � " << last_answered_question + 1 << " �������." << std::endl;
			std::cout << "�������� �������: " << correct_answers << " ���������� ��������." << std::endl;
		}

		// ��������� �� ������ �������� ������� �����
		const std::vector<TestInfo::Question>& questions = test_info.subjects[subject_index].tests[test_index].questions;

		if (questions.empty()) {
			std::cout << "�������: ���� �� ������ ��������!" << std::endl;
			return false;
		}

		total_questions = questions.size();

		for (int i = last_answered_question; i < total_questions; i++) { // ��� ����������
			std::string current_answers[4];// ������ 4 ������� ������
			for (int j = 0; j < 4; j++) {
				if (j < questions[i].answers_variants.size()) {
					current_answers[j] = questions[i].answers_variants[j];
				}
				else {
					current_answers[j] = ""; // ������� ������� ���� ������� ����� 4
				}
			}

			Question question( // ���������� ��� ������ �� ������� ��������
				questions[i].text,
				current_answers,
				questions[i].correct_answer_index,
				i + 1
			);

			int result = question.ask();
			if (result == -1) {
				std::cout << "���������� �����������. �� ������ ���������� �����" << std::endl;

				if (!username.empty()) {  // ��������� �������� �����������
					if (TestProgress::save_progress(username, subject_index, test_index, correct_answers, i)) {
						std::cout << "������� ����� ���������" << std::endl;
					}
					else {
						std::cout << "������� ��� ��������� ��������" << std::endl;
					}
				}

				return false;
			}
			else if (result == 1) {
				correct_answers++; // �������� 1 �� �������
				std::cout << "³������ ���������!" << std::endl;
			}
			else {
				std::cout << "³������ �����������." << std::endl;
			}
			std::cout << std::endl;

			last_answered_question = i + 1;

		}

		is_completed = true; // ��������� �����

		if (!username.empty()) {
			TestResult::save_result_to_file( // ���������������
				username,
				subject_name,
				test_name,
				correct_answers,
				total_questions
			);
			TestProgress::remove_progress(username, subject_index, test_index); // ������� ����� ��� �������
		}
		return true;
	}

	std::string get_name() {
		return test_name;
	}
	std::string get_subject_name() {
		return subject_name;
	}

	int get_correct_answers() {
		return correct_answers;
	}
	int get_total_questions() {
		return total_questions;
	}

	bool get_is_done() {
		return is_completed;
	}

	int get_subject_index() {
		return subject_index;
	}

	int get_test_index(){
		return test_index;
	}

	int get_count_of_subjects() {
		return test_info.subjects.size();
	}

	int get_count_of_tests() { // ���������� ������� ���������
		if (subject_index >= 0 && subject_index < test_info.subjects.size()) {
			return test_info.subjects[subject_index].tests.size();
		}
		return 0;
	}
};