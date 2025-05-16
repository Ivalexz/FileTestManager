#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

struct UnfinishedTest {  // ��������� ��� ��������� ���������� ��� ������������ ���� �� ���������� �� �����
    std::string username; // ��'� �����������
    int subject_index; // ������ ��������
    int test_index; // ������ �����
    int correct_answers; // ������� ���������� �������� �� ����� ������
    int last_answered_question; // ������ �������, �� ��� ���� �������
};

class TestProgress {
private:
    static const std::string progress_file; // ����� ����� ��� ��������� ��������
public:
    // ������� ��� ���������� �������� � ����
    static bool save_progress(std::string username, int subject_index, int test_index, int correct_answers, int last_answered_question) {
        std::ifstream file;
        std::string line;
        bool already_in_file = false; // ����� ��� �������� �� � ��� ��� ���� � ���� (�� ������� ���������� ������ � �����)
        file.open(progress_file); // �������� ����� ��� �������

        while (std::getline(file, line)) {
            std::string saved_username = line;
            std::getline(file, line); // subject_index
            int saved_subject_index = std::stoi(line); // ������������ � ���� �����
            std::getline(file, line); // test_index
            int saved_test_index = std::stoi(line); // ������������ � ���� �����
            std::getline(file, line); // correct_answers
            std::getline(file, line); // last_answered_question
            std::getline(file, line); // ��, ���� ��������� �����

            if (saved_username == username && saved_subject_index == subject_index && saved_test_index == test_index) {
                already_in_file = true;  // ����������, �� ����� ���� (�����������) ��� ����
                break;
            }
        }
        file.close();
        if (already_in_file) {
            return true; // ��� ���������; �� ������� �������� ��������
        }

        std::ofstream write_file;
        write_file.open(progress_file, std::ios::app);

        if (!write_file.is_open()) {
            return false;  // ���� ���� �� �����������
        }

        // ����� ����������
        write_file << username << std::endl;
        write_file << subject_index << std::endl;
        write_file << test_index << std::endl;
        write_file << correct_answers << std::endl;
        write_file << last_answered_question << std::endl;
        write_file << "------------------------------" << std::endl;

        file.close(); // ��������� ����
        return true;// ������� ������ ��������
    }

    // �������, ��� ������� ������ ����������� ����� ������� ����������� 
    // (������, �� �� �� ����� ������� ����� �� ��� � ������� ��������� � ����� - push_back)
    static std::vector <UnfinishedTest> get_unfinished_tests(std::string username) {
        std::vector <UnfinishedTest> unfinished_tests;
        std::ifstream file;
        file.open(progress_file); // �������� ����� � ���������

        if (!file.is_open()) {
            return unfinished_tests; // ���������� ������� ������� ���� ���� �� ������� �������
        }

        std::string line; // ����� ��� ������� �����
        while (std::getline(file, line)) { // ������ � ������ ��� � ����
            UnfinishedTest test; // ��������� �����
            test.username = line; // ����� ��� - ��������� ���� �����������

            if (test.username == username) { // ���� �� ��� ����������
                if (std::getline(file, line)) {
                    test.subject_index = std::stoi(line); // ������������ ������ � ������ � ���� �����
                }
                if (std::getline(file, line)) {
                    test.test_index = std::stoi(line); // ������������ ������ � ������ � ���� �����
                }
                if (std::getline(file, line)) {
                    test.correct_answers = std::stoi(line); // ������������ ������� � ������ � ���� �����
                }
                if (std::getline(file, line)) {
                    test.last_answered_question = std::stoi(line); // ������������ �������� � ������ � ���� �����
                }
                std::getline(file, line); // ���������� ��, �� ��������� �����
                unfinished_tests.push_back(test); // ������ ���� �� ������� ������������ ����� ����� �����������
            }
            else {
                for (size_t i = 0; i < 5; i++) // �������� �����������, ���� �� ������
                {
                    getline(file, line);
                }
            }
        }
        file.close();
        return unfinished_tests; // ���������� ������� � ������������ ������� ����� �����������
    }

    // ������� ��� ��������� ����������� ����� � ������� ������������ ����� �����������
    static bool remove_progress(std::string username, int subject_index, int test_index) {
        std::vector<UnfinishedTest> all_tests;  // � ��� ������ �� ������ �������������� ��������� ��� �����, ������ ������� ��������
        
        std::ifstream file;
        file.open(progress_file); // �������� ����� � ���������

        if (!file.is_open()) {
            return false; // ���� ���� �� ������� �������
        }
        
        std::string line; // ����� ��� ������� �����

        while (std::getline(file, line)) { // ������ � ������ ��� � ����
            UnfinishedTest test; // ��������� �����
            test.username = line; // ����� ��� - ��������� ���� �����������


            // ����� ������� �� ���� ������� ����� � ����� �� ������������ �������� � ����� � �����
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
            std::getline(file, line); // ���������� ��, �� ��������� ������������
            
            // ��������� �� �� �� ��� ����, ���� ������� ��������
            if (!(test.username == username && test.subject_index == subject_index && test.test_index == test_index)) {
                all_tests.push_back(test); // ������ ��� ���� �� ������ �������
            }
        }
        file.close(); // ��������� ����

        std::remove("test_progress.txt"); // ��������� ����

        std::ofstream new_file; // ����� �������� ���� ��� ������ �������� ����������
        new_file.open(progress_file, std::ios::app); // �������� ����� ��� ������ � �����
        if (!new_file.is_open()) { // ���� ���� �� ��������
            return false; // �������� � ��������� �����
        }
        
        for (auto& test : all_tests) {   // ������������ ���� ��� ���������� �����
            new_file << test.username << std::endl;
            new_file << test.subject_index << std::endl;
            new_file << test.test_index << std::endl;
            new_file << test.correct_answers << std::endl;
            new_file << test.last_answered_question << std::endl;
            new_file << "------------------------------" << std::endl;
        }

        new_file.close(); // ��������� ����
        return true; // ��������� ������� ������
    }
};