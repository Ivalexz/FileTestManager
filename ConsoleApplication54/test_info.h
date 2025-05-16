#pragma once
#include <vector>
#include <string>

class TestInfo { // клас для реалізації заповнення інформації про тест
public:
    struct Question { // структура для запитань
        std::string text;
        std::vector<std::string> answers_variants;
        int correct_answer_index;
    };

    struct TestStruct {// структура для тестів
        std::string subject; // назва предмету
        std::string test_name; //назва тесту
        std::vector<Question> questions;
    };

    struct Subject {//структура для предметів
        std::string name;
        std::vector<TestStruct> tests;
    };

    static std::vector<Subject> subjects;//вектор предметів

    // для додавання предметів/тестів/запитань адміном
    static void add_subject(std::string subject_name);
    static void add_test(std::string subject_name, std::string test_name);
    static void add_question(std::string subject_name, std::string test_name, std::string question_text, std::vector<std::string> answers_variants, int correct_answer_index);

    static void save_tests_to_file(std::string file_name); // для збереження тестів у файл
    static std::vector<TestStruct> get_tests_from_file(std::string file_name); //для вигруження тестів з файлу
    static void get_all_default_questions(); //вигружає усі дефолтні тести


};