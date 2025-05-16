#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

struct Results {  // структура для зберігання інформації про результати
    std::string username; // логін користувача
    std::string subject_name;// назва предмету
    std::string test_name;  // назва тесту
    int correct_answers;  //   кількість правильних відповідей
    int total_questions;   // загальна кількість запитань
    double percent; // % правильних відповідей
    int grade; // оцінка в 12 балах
};
class TestResult {  // обчислення результатів тестування
private:
    static const std::string result_file; // назва файлу для зберігання результатів
public:
    static int calculate_grade(int correct, int total) {
        return (correct * 12) / total; //обчислення оцінки
    }
    static double calculate_percent(int correct, int total) {
        return ((double)correct * 100) / total; //обчислення проценту
    }
    static bool save_result_to_file(std::string username, std::string subject_name, std::string test_name, int correct_answers, int total_questions) {
        std::ofstream file(result_file, std::ios::app);

        if (file.is_open()) {
            file << username << std::endl;
            file << subject_name << std::endl;
            file << test_name << std::endl;
            file << correct_answers << std::endl;
            file << total_questions << std::endl;
            file << calculate_percent(correct_answers, total_questions) << std::endl;
            file << calculate_grade(correct_answers, total_questions) << std::endl;
            file << "------------------------------" << std::endl;
            file.close();
            return true;
        }
        return false; // якщо файл не вдалось відкрити
    }

    static std::vector<Results> get_user_results(std::string username) {  // отримати усі результати певного користувача
        std::vector <Results> all_user_results; // вектор з усіма результатами певного користувача
        std::ifstream file;
        file.open(result_file); // відкриття файлу з результатами

        if (!file.is_open()) {
            return all_user_results; // повернення пустого вектора якщо файл не вдалось відкрити
        }

        std::string line; // рядки для читання файлу
        while (std::getline(file, line)) { // робота з кожною лінією у файлі
            Results result; // структура результату
            result.username = line; // перша лінія - унікальний логін користувача

            if (result.username == username) { // якщо це наш користувач
                if (std::getline(file, line)) {
                    result.subject_name = line;
                }
                if (std::getline(file, line)) {
                    result.test_name = line;
                }
                if (std::getline(file, line)) {
                    result.correct_answers = std::stoi(line); // перетворення значення з стрінги в число
                }
                if (std::getline(file, line)) {
                    result.total_questions = std::stoi(line); // перетворення значення з стрінги в число
                }
                if (std::getline(file, line)) {
                    result.percent = std::stod(line); // перетворення значення з стрінги в число (double)
                }
                if (std::getline(file, line)) {
                    result.grade = std::stoi(line); // перетворення значення з стрінги в число
                }
                std::getline(file, line); // пропускаємо лінії, які розділяють результати

                all_user_results.push_back(result); // додаємо результат до вектору усіх результатів цього користувача
            }
            else {
                for (size_t i = 0; i < 5; i++) // пропускає користувача, який не підійшов
                {
                    getline(file, line);
                }
            }
        }
        file.close();
        return all_user_results; // повертання вектора з незакінченими тестами цього користувача
    }

    static void show_user_results(std::string username) { // вивід усіх результатів користувача
        std::vector<Results> all_results = get_user_results(username); // усі результати користувача

        if (all_results.empty()) { // якщо вектор пустий і користувача не знайдено
            std::cout << "Результати для користувача " << username << " не знайдено" << std::endl;
        }
        else {
            std::cout << "===== Результати тестування для користувача " << username << " =====" << std::endl;
            for (const auto& res : all_results) {
                std::cout << "Предмет: " << res.subject_name << std::endl;
                std::cout << "Тест: " << res.test_name << std::endl;
                std::cout << "Правильних відповідей: " << res.correct_answers << "/" << res.total_questions << std::endl;
                std::cout << "Відсоток: " << res.percent << "%" << std::endl;
                std::cout << "Оцінка: " << res.grade << "/12" << std::endl;
                std::cout << "------------------------------" << std::endl;
            }
        }
    }
    static std::vector<Results> get_test_result(std::string subject_name, std::string test_name) {
        std::vector <Results> all_test_results; // вектор з усіма результатами по певному тесту
        std::ifstream file;
        file.open(result_file); // відкриття файлу з результатами

        if (!file.is_open()) {
            return all_test_results; // повернення пустого вектора якщо файл не вдалось відкрити
        }

        std::string line; // рядки для читання файлу
        while (file) { // проходимось по цілому файлі
            std::string curr_username, curr_subject, curr_test;
            int correct, total, grade;
            double percent;

            if (std::getline(file, line)) {
                curr_username = line; // читаємо поточний логін
            }
            if (std::getline(file, line)) {
                curr_subject = line; // читаємо поточний предмет
            }
            if (std::getline(file, line)) {
                curr_test = line; // читаємо поточний тест
            }
            if (std::getline(file, line)) {
                correct = std::stoi(line); // перетворення кількості правильних відповідей з стрінги в число
            }
            if (std::getline(file, line)) {
                total = std::stoi(line); // перетворення загальної кількості запитань з стрінги в число
            }
            if (std::getline(file, line)) {
                percent = std::stod(line); // перетворення % з стрінги в число (double)
            }
            if (std::getline(file, line)) {
                grade = std::stoi(line); // перетворення оцінки з стрінги в число
            }
            std::getline(file, line); // пропускаємо лінії, які розділяють результати
            if (curr_subject == subject_name && curr_test == test_name) {
                // якщо все збігається, створюємо новий результат і додаємо його до вектора
                Results result;
                result.username = curr_username;
                result.subject_name = curr_subject;
                result.test_name = curr_test;
                result.correct_answers = correct;
                result.total_questions = total;
                result.percent = percent;
                result.grade = grade;
                all_test_results.push_back(result); // додаємо результат до вектору усіх результатів цього користувача

            }
        }
        file.close();
        return all_test_results;
    }
    static void show_test_result(std::string subject_name, std::string test_name) {
        std::vector<Results> all_test_result = get_test_result(subject_name, test_name); // усі результати користувача

        if (all_test_result.empty()) { // якщо вектор пустий і користувача не знайдено
            std::cout << "Результати за тестом " << test_name << " не знайдено" << std::endl;
        }
        else {
            std::cout << "===== Результати тестування '" << test_name << "' за предметом '"<<subject_name<<"' ==== = " << std::endl;
            for (const auto& res : all_test_result) {
                std::cout << "Користувач: " << res.username << std::endl;
                std::cout << "Правильних відповідей: " << res.correct_answers << "/" << res.total_questions << std::endl;
                std::cout << "Відсоток: " << res.percent << "%" << std::endl;
                std::cout << "Оцінка: " << res.grade << "/12" << std::endl;
                std::cout << "------------------------------" << std::endl;
            }
        }
    }

    static void show_result_for_test_end(std::string username, std::string subject_name, std::string test_name) {
        std::vector<Results> all_user_test_result = get_test_result(subject_name, test_name);

        if (all_user_test_result.empty()) {
            std::cout << "Результати для користувача " << username << " не знайдено" << std::endl;
        }
        else {
            const Results& res = all_user_test_result.back(); // останній елемент вектора — остання спроба
            std::cout << "===== Результат пройденого тестування для користувача =====" << std::endl;
            std::cout << "Предмет: " << res.subject_name << std::endl;
            std::cout << "Тест: " << res.test_name << std::endl;
            std::cout << "Правильних відповідей: " << res.correct_answers << "/" << res.total_questions << std::endl;
            std::cout << "Відсоток: " << res.percent << "%" << std::endl;
            std::cout << "Оцінка: " << res.grade << "/12" << std::endl;
            std::cout << "------------------------------" << std::endl;
        }
    }

    static std::vector<Results> get_subject_result(std::string subject_name) {
        std::vector <Results> all_subject_results; // вектор з усіма результатами по певному предмету
        std::ifstream file;
        file.open(result_file); // відкриття файлу з результатами

        if (!file.is_open()) {
            return all_subject_results; // повернення пустого вектора якщо файл не вдалось відкрити
        }
        std::string line; // рядки для читання файлу
        while (file) { // проходимось по цілому файлі
            std::string curr_username,curr_subject, curr_test;
            int correct, total, grade;
            double percent;

            if (std::getline(file, line)) {
                curr_username = line; // читаємо поточний логін
            }
            if (std::getline(file, line)) {
                curr_subject = line; // читаємо поточний предмет
            }
            if (std::getline(file, line)) {
                curr_test = line; // читаємо поточний тест
            }
            if (std::getline(file, line)) {
                correct = std::stoi(line); // перетворення кількості правильних відповідей з стрінги в число
            }
            if (std::getline(file, line)) {
                total = std::stoi(line); // перетворення загальної кількості запитань з стрінги в число
            }
            if (std::getline(file, line)) {
                percent = std::stod(line); // перетворення % з стрінги в число (double)
            }
            if (std::getline(file, line)) {
                grade = std::stoi(line); // перетворення оцінки з стрінги в число
            }
            std::getline(file, line); // пропускаємо лінії, які розділяють результати
            if (curr_subject == subject_name) {
                // якщо все збігається, створюємо новий результат і додаємо його до вектора
                Results result;
                result.username = curr_username;
                result.subject_name = curr_subject;
                result.test_name = curr_test;
                result.correct_answers = correct;
                result.total_questions = total;
                result.percent = percent;
                result.grade = grade;
                all_subject_results.push_back(result); // додаємо результат до вектору усіх результатів цього користувача

            }
        }
        file.close();
        return all_subject_results;
    }

    static void show_subject_result(std::string subject_name) {
        std::vector<Results> all_subject_result = get_subject_result(subject_name); // усі результати за предметом

        if (all_subject_result.empty()) { // якщо вектор пустий і предмет не знайдено
            std::cout << "Результати за предметом " << subject_name << " не знайдено" << std::endl;
        }
        else {
            std::cout << "===== Результати за предметом '" << subject_name << "' ==== = " << std::endl;
            for (const auto& res : all_subject_result) {
                std::cout << "Тест: " << res.test_name << std::endl;
                std::cout << "Користувач: " << res.username << std::endl;
                std::cout << "Правильних відповідей: " << res.correct_answers << "/" << res.total_questions << std::endl;
                std::cout << "Відсоток: " << res.percent << "%" << std::endl;
                std::cout << "Оцінка: " << res.grade << "/12" << std::endl;
                std::cout << "------------------------------" << std::endl;
            }
        }
    }

};