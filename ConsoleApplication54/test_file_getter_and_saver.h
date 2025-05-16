#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class TestFileGetterAndSaver{ // клас для читання тестів з файлу та їх збереження
public:
      //завантаження тестів з файлу у динамічні масиви (переважно багатовимірні)
    static bool read_tests_from_file(const std::string& filename,
        std::string**& subjects, int& subject_count, // масив назв предметів
        std::string***& tests, int* test_counts, // масив тестів у кожному предметі
        std::string****& questions, int** question_counts, // запитання в кожному тесті
        std::string*****& answers, int*** answer_counts, // відповіді до кожного запитання
        int***& correct_answers // правильні відповіді до кожного запитання
    );

    //предмет > тести > запитання > відповіді >правильні варіанти

    static bool save_tests_to_file(const std::string& filename, //збереження тестів у файл з динамічних масивів
        std::string** subjects, int subject_count,
        std::string*** tests, int* test_counts,
        std::string**** questions, int** question_counts,
        std::string***** answers, int*** answer_counts,
        int*** correct_answers
    );

    static bool save_default_tests_to_file(const std::string& filename);  // функція для зберігання стандартних тестів у файл
};