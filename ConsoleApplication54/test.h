#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "question.h"
#include "exception_function.h"
#include "test_info.h"
#include "test_result.h"
#include "test_progress.h"

class Test { // клас для реалізації основної логіки тестуваня
private:
	TestResult* result; // результат тесту з файлу TestResult
	std::string test_name; // назва тесту
	std::string subject_name; // назва предмету
	int subject_index; // індекс предмету
	int test_index; // індекс цього тесту в предметі
	int correct_answers; // кількість правильних відповідей
	int total_questions; // загальна кількість запитань у цьому тесті
	bool is_completed; // чи завершено тест
	int last_answered_question; // номер останнього відповіденого запитання (для продовження)
	std::string username; // логін користувача для відстеження прогресу в тесті
	
	static const std::string test_file_name; // константна назва файлу для збереження тестів
	static TestInfo test_info; // статичний об'єкт для доступу до інформації про тести

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
			this->subject_name = "Невідомий предмет";
			this->test_name = "Невідомий тест";
			this->total_questions = 0;
		}
	}
	// конструктор для роботи з прогресом в тестуванні
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
			this->subject_name = "Невідомий предмет";
			this->test_name = "Невідомий тест";
			this->total_questions = 0;
		}
	}

	static void start_program_get_all_test() {// при запуску програми вигружає усі тести
		test_info.get_all_default_questions(); //завантажує дефолтні питання

		try {  // пробує завантажити з файлу (якщо вони є)
			std::vector<TestInfo::TestStruct> taken_tests = test_info.get_tests_from_file(test_file_name);
			if (taken_tests.empty()) {
				throw 404;
			}
			else {
				std::cout << "Тести успішно завантажені з файлу" << std::endl;
			}
		}
		catch (...) {
			std::cout << "Помилка при завантаженні тестів з файлу" << std::endl;
			std::cout << "Використовуються дефолтні тести" << std::endl;

			test_info.save_tests_to_file(test_file_name); //зберігає дефолтні тести у файл для використання потім
		}
	}

	static std::vector<std::string> get_subject_list() { // геттер для отримання списку(вектору) предметів
		std::vector<std::string> subject_names;
		for (const auto& subject : test_info.subjects) {
			subject_names.push_back(subject.name);
		}
		return subject_names;
	}

	static std::vector<std::string> get_test_list(int subject_index) { // геттер для отримання списку(вектору) тестів
		std::vector<std::string> test_names;
		if (subject_index >= 0 && subject_index < test_info.subjects.size()) {// чи коректний індекс
			for (const auto& test : test_info.subjects[subject_index].tests) {
				test_names.push_back(test.test_name);
			}
		}
		return test_names;
	}

	void set_username(const std::string username) {  // встановленя логіну користувача для прогресу
		this->username = username;
	}

	bool run() {
		if (subject_index < 0 || test_index < 0 || subject_index >= test_info.subjects.size() || test_index >= test_info.subjects[subject_index].tests.size()) {
			std::cout << "Помилка: такого тесту неіснує" << std::endl;
			return false;
		}
		std::cout << "ІНСТРУКЦІЯ: після кожного запитання у поле вводу записуйте коротку відповідь у ЦИФРОВОМУ форматі"<<std::endl<<"Приклад: 1 (перша відповідь)" << std::endl<<"Натисніть '0' для виходу" << std::endl << "УСПІХІВ!" << std::endl;
		std::cout << "===== Тест: " << test_name << "=====" << std::endl;

		 // якщо користувач повертається до незакінченого тесту
		if (last_answered_question > 0) {
			std::cout << "Продовження тесту з " << last_answered_question + 1 << " питання." << std::endl;
			std::cout << "Поточний рахунок: " << correct_answers << " правильних відповідей." << std::endl;
		}

		// посилання на вектор запитань певного тесту
		const std::vector<TestInfo::Question>& questions = test_info.subjects[subject_index].tests[test_index].questions;

		if (questions.empty()) {
			std::cout << "Помилка: тест не містить запитань!" << std::endl;
			return false;
		}

		total_questions = questions.size();

		for (int i = last_answered_question; i < total_questions; i++) { // йде тестування
			std::string current_answers[4];// всього 4 варіанти відповіді
			for (int j = 0; j < 4; j++) {
				if (j < questions[i].answers_variants.size()) {
					current_answers[j] = questions[i].answers_variants[j];
				}
				else {
					current_answers[j] = ""; // порожня відповідь коли варіантів менше 4
				}
			}

			Question question( // передається для виводу та обробки відповідей
				questions[i].text,
				current_answers,
				questions[i].correct_answer_index,
				i + 1
			);

			int result = question.ask();
			if (result == -1) {
				std::cout << "Тестування призупинено. Ви можете продовжити пізніше" << std::endl;

				if (!username.empty()) {  // зберігання прогресу користувача
					if (TestProgress::save_progress(username, subject_index, test_index, correct_answers, i)) {
						std::cout << "Прогрес тесту збережено" << std::endl;
					}
					else {
						std::cout << "Помилка при збереженні прогресу" << std::endl;
					}
				}

				return false;
			}
			else if (result == 1) {
				correct_answers++; // додається 1 до рахунку
				std::cout << "Відповідь правильна!" << std::endl;
			}
			else {
				std::cout << "Відповідь неправильна." << std::endl;
			}
			std::cout << std::endl;

			last_answered_question = i + 1;

		}

		is_completed = true; // закінчення тесту

		if (!username.empty()) {
			TestResult::save_result_to_file( // зберігаєрезультат
				username,
				subject_name,
				test_name,
				correct_answers,
				total_questions
			);
			TestProgress::remove_progress(username, subject_index, test_index); // видаляє запис про прогрес
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

	int get_count_of_tests() { // розрахунок кількості тестувань
		if (subject_index >= 0 && subject_index < test_info.subjects.size()) {
			return test_info.subjects[subject_index].tests.size();
		}
		return 0;
	}
};