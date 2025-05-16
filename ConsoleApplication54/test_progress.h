#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

struct UnfinishedTest {  // структура для зберігання інформації про незавершений тест та повернення до нього
    std::string username; // ім'я користувача
    int subject_index; // індекс предмету
    int test_index; // індекс тесту
    int correct_answers; // кількість правильних відповідей на даний момент
    int last_answered_question; // останнє питання, на яке дали відповідь
};

class TestProgress {
private:
    static const std::string progress_file; // назва файлу для зберігання прогресу
public:
    // функція для збереження прогресу в файлі
    static bool save_progress(std::string username, int subject_index, int test_index, int correct_answers, int last_answered_question) {
        std::ifstream file;
        std::string line;
        bool already_in_file = false; // змінна для перевірки чи є вже цей тест у файлі (на випадок повторного виходу з тесту)
        file.open(progress_file); // відкриття файлу для читання

        while (std::getline(file, line)) {
            std::string saved_username = line;
            std::getline(file, line); // subject_index
            int saved_subject_index = std::stoi(line); // перетворення у ціле число
            std::getline(file, line); // test_index
            int saved_test_index = std::stoi(line); // перетворення у ціле число
            std::getline(file, line); // correct_answers
            std::getline(file, line); // last_answered_question
            std::getline(file, line); // лінії, котрі розділяють тести

            if (saved_username == username && saved_subject_index == subject_index && saved_test_index == test_index) {
                already_in_file = true;  // зазначення, що такий тест (незакінчений) вже існує
                break;
            }
        }
        file.close();
        if (already_in_file) {
            return true; // уже збережено; не потрібно додавати повторно
        }

        std::ofstream write_file;
        write_file.open(progress_file, std::ios::app);

        if (!write_file.is_open()) {
            return false;  // коли файл не відкривається
        }

        // запис інформації
        write_file << username << std::endl;
        write_file << subject_index << std::endl;
        write_file << test_index << std::endl;
        write_file << correct_answers << std::endl;
        write_file << last_answered_question << std::endl;
        write_file << "------------------------------" << std::endl;

        file.close(); // закриваємо файл
        return true;// функція успішно виконана
    }

    // функція, яка повертає вектор незакінчених тестів певного користувача 
    // (вектор, бо ми не знаємо кількості тестів та тут є функція додавання в кінець - push_back)
    static std::vector <UnfinishedTest> get_unfinished_tests(std::string username) {
        std::vector <UnfinishedTest> unfinished_tests;
        std::ifstream file;
        file.open(progress_file); // відкриття файлу з прогресом

        if (!file.is_open()) {
            return unfinished_tests; // повернення пустого вектора якщо файл не вдалось відкрити
        }

        std::string line; // рядки для читання файлу
        while (std::getline(file, line)) { // робота з кожною лінією у файлі
            UnfinishedTest test; // структура тесту
            test.username = line; // перша лінія - унікальний логін користувача

            if (test.username == username) { // якщо це наш користувач
                if (std::getline(file, line)) {
                    test.subject_index = std::stoi(line); // перетворюємо індекс з стрінги в ціле число
                }
                if (std::getline(file, line)) {
                    test.test_index = std::stoi(line); // перетворюємо індекс з стрінги в ціле число
                }
                if (std::getline(file, line)) {
                    test.correct_answers = std::stoi(line); // перетворюємо кількість з стрінги в ціле число
                }
                if (std::getline(file, line)) {
                    test.last_answered_question = std::stoi(line); // перетворюємо значення з стрінги в ціле число
                }
                std::getline(file, line); // пропускаємо лінії, які розділяють тести
                unfinished_tests.push_back(test); // додаємо тест до вектору незавершених тестів цього користувача
            }
            else {
                for (size_t i = 0; i < 5; i++) // пропускає користувача, який не підійшов
                {
                    getline(file, line);
                }
            }
        }
        file.close();
        return unfinished_tests; // повертання вектора з незакінченими тестами цього користувача
    }

    // функція для видалення ЗАВЕРШЕНОГО тесту з вектора незавершених тестів користувача
    static bool remove_progress(std::string username, int subject_index, int test_index) {
        std::vector<UnfinishedTest> all_tests;  // у цей вектор ми будемо перезаписувати попередній без теста, котрий потрібно видалити
        
        std::ifstream file;
        file.open(progress_file); // відкриття файлу з прогресом

        if (!file.is_open()) {
            return false; // якщо файл не вдалось відкрити
        }
        
        std::string line; // рядок для читання файлу

        while (std::getline(file, line)) { // робота з кожною лінією у файлі
            UnfinishedTest test; // структура тесту
            test.username = line; // перша лінія - унікальний логін користувача


            // знову зчитуємо усі поля кожного тесту з файлу та перетворюємо значення з рядків у числа
            if (std::getline(file, line)) {
                test.subject_index = std::stoi(line);
            }
            if (std::getline(file, line)) {
                test.test_index = std::stoi(line);
            }
            if (std::getline(file, line)) {
                test.correct_answers = std::stoi(line);
            }
            if (std::getline(file, line)) {
                test.last_answered_question = std::stoi(line);
            }
            std::getline(file, line); // пропускаємо лінії, які розділяють користувачів
            
            // первіряємо чи це НЕ той тест, який потрібно видалити
            if (!(test.username == username && test.subject_index == subject_index && test.test_index == test_index)) {
                all_tests.push_back(test); // додаємо цей тест до нового вектора
            }
        }
        file.close(); // закриваємо файл

        std::remove("test_progress.txt"); // видаляємо файл

        std::ofstream new_file; // знову стіорюємо файл для запису оновленої інформації
        new_file.open(progress_file, std::ios::app); // відкриття файлу для запису у кінець
        if (!new_file.is_open()) { // якщо файл не відкрився
            return false; // проблема з відкриттям файлу
        }
        
        for (auto& test : all_tests) {   // перезаписуємо файл без видаленого тесту
            new_file << test.username << std::endl;
            new_file << test.subject_index << std::endl;
            new_file << test.test_index << std::endl;
            new_file << test.correct_answers << std::endl;
            new_file << test.last_answered_question << std::endl;
            new_file << "------------------------------" << std::endl;
        }

        new_file.close(); // закриваємо файл
        return true; // видалення пройшло успішно
    }
};