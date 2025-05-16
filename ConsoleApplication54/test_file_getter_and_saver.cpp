#include "test_file_getter_and_saver.h"

#include "test_info.h"

bool TestFileGetterAndSaver::read_tests_from_file(const std::string& filename,
    std::string**& subjects, int& subject_count,
    std::string***& tests, int* test_counts,
    std::string****& questions, int** question_counts,
    std::string*****& answers, int*** answer_counts,
    int***& correct_answers)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл: " << filename << std::endl;
        return false;
    }
    file >> subject_count;

    subjects = new std::string * [subject_count]; // масив предметів
    tests = new std::string * *[subject_count]; // масив тестів
    test_counts = new int[subject_count];
    questions = new std::string * **[subject_count]; // масив питань
    question_counts = new int* [subject_count];
    answers = new std::string * ***[subject_count]; // масив варіантів відповідей
    answer_counts = new int** [subject_count];
    correct_answers = new int** [subject_count];//масив правильних відповідей

    for (int i = 0; i < subject_count; ++i) { // проходимось по усіх предметах
        subjects[i] = new std::string;
        std::getline(file, *subjects[i]);

        file >> test_counts[i];
        file.ignore();

        tests[i] = new std::string * [test_counts[i]];
        questions[i] = new std::string * *[test_counts[i]];
        answers[i] = new std::string * **[test_counts[i]];
        correct_answers[i] = new int* [test_counts[i]];
        question_counts[i] = new int[test_counts[i]];
        answer_counts[i] = new int* [test_counts[i]];

        for (int j = 0; j < test_counts[i]; ++j) {
            tests[i][j] = new std::string;
            std::getline(file, *tests[i][j]);

            file >> question_counts[i][j];
            file.ignore();

            questions[i][j] = new std::string * [question_counts[i][j]];
            answers[i][j] = new std::string * *[question_counts[i][j]];
            correct_answers[i][j] = new int[question_counts[i][j]];
            answer_counts[i][j] = new int[question_counts[i][j]];

            for (int k = 0; k < question_counts[i][j]; ++k) {
                questions[i][j][k] = new std::string;
                std::getline(file, *questions[i][j][k]);

                file >> answer_counts[i][j][k];
                file.ignore();

                answers[i][j][k] = new std::string * [answer_counts[i][j][k]];

                for (int l = 0; l < answer_counts[i][j][k]; ++l) {
                    answers[i][j][k][l] = new std::string;
                    std::getline(file, *answers[i][j][k][l]);
                }

                file >> correct_answers[i][j][k];
                file.ignore();
            }
        }
    }

    file.close();
    return true;
}

bool TestFileGetterAndSaver::save_tests_to_file(const std::string& filename,
    std::string** subjects, int subject_count,
    std::string*** tests, int* test_counts,
    std::string**** questions, int** question_counts,
    std::string***** answers, int*** answer_counts,
    int*** correct_answers)
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл для запису: " << filename << std::endl;
        return false;
    }

    file << subject_count << "\n";
    for (int i = 0; i < subject_count; ++i) {
        file << *subjects[i] << "\n";
        file << test_counts[i] << "\n";
        for (int j = 0; j < test_counts[i]; ++j) {
            file << *tests[i][j] << "\n";
            file << question_counts[i][j] << "\n";
            for (int k = 0; k < question_counts[i][j]; ++k) {
                file << *questions[i][j][k] << "\n";
                file << answer_counts[i][j][k] << "\n";
                for (int l = 0; l < answer_counts[i][j][k]; ++l) {
                    file << *answers[i][j][k][l] << "\n";
                }
                file << correct_answers[i][j][k] << "\n";
            }
        }
    }

    file.close();
    return true;
}

bool TestFileGetterAndSaver::save_default_tests_to_file(const std::string& filename)
{
    TestInfo::fill_questions_and_answers();

    int subject_count = TestInfo::count_of_subjects;
    int* test_counts = new int[subject_count];
    int** question_counts = new int* [subject_count];
    int*** answer_counts = new int** [subject_count];

    std::string** subjects = new std::string * [subject_count];
    std::string*** tests = new std::string * *[subject_count];
    std::string**** questions = new std::string * **[subject_count];
    std::string***** answers = new std::string * ***[subject_count];
    int*** correct_answers = new int** [subject_count];

    for (int i = 0; i < subject_count; ++i) {
        subjects[i] = new std::string(TestInfo::subjects[i]);
        test_counts[i] = TestInfo::count_of_tests;

        tests[i] = new std::string * [test_counts[i]];
        questions[i] = new std::string * *[test_counts[i]];
        answers[i] = new std::string * **[test_counts[i]];
        correct_answers[i] = new int* [test_counts[i]];
        question_counts[i] = new int[test_counts[i]];
        answer_counts[i] = new int* [test_counts[i]];

        for (int j = 0; j < test_counts[i]; ++j) {
            tests[i][j] = new std::string(TestInfo::tests[i][j]);
            question_counts[i][j] = TestInfo::count_of_questions;

            questions[i][j] = new std::string * [question_counts[i][j]];
            answers[i][j] = new std::string * *[question_counts[i][j]];
            correct_answers[i][j] = new int[question_counts[i][j]];
            answer_counts[i][j] = new int[question_counts[i][j]];

            for (int k = 0; k < question_counts[i][j]; ++k) {
                questions[i][j][k] = new std::string(TestInfo::questions[i][j][k]);
                answer_counts[i][j][k] = TestInfo::answer_options;

                answers[i][j][k] = new std::string * [answer_counts[i][j][k]];
                for (int l = 0; l < answer_counts[i][j][k]; ++l) {
                    answers[i][j][k][l] = new std::string(TestInfo::answers[i][j][k][l]);
                }

                correct_answers[i][j][k] = TestInfo::correct_answers[i][j][k];
            }
        }
    }

    bool result = save_tests_to_file(filename, subjects, subject_count, tests, test_counts, questions, question_counts, answers, answer_counts, correct_answers);

    // TODO: Очищення памʼяті (не забудь реалізувати або додати функцію clean_tests_data)

    return result;
}