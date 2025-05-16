#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

struct Results {  // ��������� ��� ��������� ���������� ��� ����������
    std::string username; // ���� �����������
    std::string subject_name;// ����� ��������
    std::string test_name;  // ����� �����
    int correct_answers;  //   ������� ���������� ��������
    int total_questions;   // �������� ������� ��������
    double percent; // % ���������� ��������
    int grade; // ������ � 12 �����
};
class TestResult {  // ���������� ���������� ����������
private:
    static const std::string result_file; // ����� ����� ��� ��������� ����������
public:
    static int calculate_grade(int correct, int total) {
        return (correct * 12) / total; //���������� ������
    }
    static double calculate_percent(int correct, int total) {
        return ((double)correct * 100) / total; //���������� ��������
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
        return false; // ���� ���� �� ������� �������
    }

    static std::vector<Results> get_user_results(std::string username) {  // �������� �� ���������� ������� �����������
        std::vector <Results> all_user_results; // ������ � ���� ������������ ������� �����������
        std::ifstream file;
        file.open(result_file); // �������� ����� � ������������

        if (!file.is_open()) {
            return all_user_results; // ���������� ������� ������� ���� ���� �� ������� �������
        }

        std::string line; // ����� ��� ������� �����
        while (std::getline(file, line)) { // ������ � ������ ��� � ����
            Results result; // ��������� ����������
            result.username = line; // ����� ��� - ��������� ���� �����������

            if (result.username == username) { // ���� �� ��� ����������
                if (std::getline(file, line)) {
                    result.subject_name = line;
                }
                if (std::getline(file, line)) {
                    result.test_name = line;
                }
                if (std::getline(file, line)) {
                    result.correct_answers = std::stoi(line); // ������������ �������� � ������ � �����
                }
                if (std::getline(file, line)) {
                    result.total_questions = std::stoi(line); // ������������ �������� � ������ � �����
                }
                if (std::getline(file, line)) {
                    result.percent = std::stod(line); // ������������ �������� � ������ � ����� (double)
                }
                if (std::getline(file, line)) {
                    result.grade = std::stoi(line); // ������������ �������� � ������ � �����
                }
                std::getline(file, line); // ���������� ��, �� ��������� ����������

                all_user_results.push_back(result); // ������ ��������� �� ������� ��� ���������� ����� �����������
            }
            else {
                for (size_t i = 0; i < 5; i++) // �������� �����������, ���� �� ������
                {
                    getline(file, line);
                }
            }
        }
        file.close();
        return all_user_results; // ���������� ������� � ������������ ������� ����� �����������
    }

    static void show_user_results(std::string username) { // ���� ��� ���������� �����������
        std::vector<Results> all_results = get_user_results(username); // �� ���������� �����������

        if (all_results.empty()) { // ���� ������ ������ � ����������� �� ��������
            std::cout << "���������� ��� ����������� " << username << " �� ��������" << std::endl;
        }
        else {
            std::cout << "===== ���������� ���������� ��� ����������� " << username << " =====" << std::endl;
            for (const auto& res : all_results) {
                std::cout << "�������: " << res.subject_name << std::endl;
                std::cout << "����: " << res.test_name << std::endl;
                std::cout << "���������� ��������: " << res.correct_answers << "/" << res.total_questions << std::endl;
                std::cout << "³������: " << res.percent << "%" << std::endl;
                std::cout << "������: " << res.grade << "/12" << std::endl;
                std::cout << "------------------------------" << std::endl;
            }
        }
    }
    static std::vector<Results> get_test_result(std::string subject_name, std::string test_name) {
        std::vector <Results> all_test_results; // ������ � ���� ������������ �� ������� �����
        std::ifstream file;
        file.open(result_file); // �������� ����� � ������������

        if (!file.is_open()) {
            return all_test_results; // ���������� ������� ������� ���� ���� �� ������� �������
        }

        std::string line; // ����� ��� ������� �����
        while (file) { // ����������� �� ������ ����
            std::string curr_username, curr_subject, curr_test;
            int correct, total, grade;
            double percent;

            if (std::getline(file, line)) {
                curr_username = line; // ������ �������� ����
            }
            if (std::getline(file, line)) {
                curr_subject = line; // ������ �������� �������
            }
            if (std::getline(file, line)) {
                curr_test = line; // ������ �������� ����
            }
            if (std::getline(file, line)) {
                correct = std::stoi(line); // ������������ ������� ���������� �������� � ������ � �����
            }
            if (std::getline(file, line)) {
                total = std::stoi(line); // ������������ �������� ������� �������� � ������ � �����
            }
            if (std::getline(file, line)) {
                percent = std::stod(line); // ������������ % � ������ � ����� (double)
            }
            if (std::getline(file, line)) {
                grade = std::stoi(line); // ������������ ������ � ������ � �����
            }
            std::getline(file, line); // ���������� ��, �� ��������� ����������
            if (curr_subject == subject_name && curr_test == test_name) {
                // ���� ��� ��������, ��������� ����� ��������� � ������ ���� �� �������
                Results result;
                result.username = curr_username;
                result.subject_name = curr_subject;
                result.test_name = curr_test;
                result.correct_answers = correct;
                result.total_questions = total;
                result.percent = percent;
                result.grade = grade;
                all_test_results.push_back(result); // ������ ��������� �� ������� ��� ���������� ����� �����������

            }
        }
        file.close();
        return all_test_results;
    }
    static void show_test_result(std::string subject_name, std::string test_name) {
        std::vector<Results> all_test_result = get_test_result(subject_name, test_name); // �� ���������� �����������

        if (all_test_result.empty()) { // ���� ������ ������ � ����������� �� ��������
            std::cout << "���������� �� ������ " << test_name << " �� ��������" << std::endl;
        }
        else {
            std::cout << "===== ���������� ���������� '" << test_name << "' �� ��������� '"<<subject_name<<"' ==== = " << std::endl;
            for (const auto& res : all_test_result) {
                std::cout << "����������: " << res.username << std::endl;
                std::cout << "���������� ��������: " << res.correct_answers << "/" << res.total_questions << std::endl;
                std::cout << "³������: " << res.percent << "%" << std::endl;
                std::cout << "������: " << res.grade << "/12" << std::endl;
                std::cout << "------------------------------" << std::endl;
            }
        }
    }

    static void show_result_for_test_end(std::string username, std::string subject_name, std::string test_name) {
        std::vector<Results> all_user_test_result = get_test_result(subject_name, test_name);

        if (all_user_test_result.empty()) {
            std::cout << "���������� ��� ����������� " << username << " �� ��������" << std::endl;
        }
        else {
            const Results& res = all_user_test_result.back(); // ������� ������� ������� � ������� ������
            std::cout << "===== ��������� ���������� ���������� ��� ����������� =====" << std::endl;
            std::cout << "�������: " << res.subject_name << std::endl;
            std::cout << "����: " << res.test_name << std::endl;
            std::cout << "���������� ��������: " << res.correct_answers << "/" << res.total_questions << std::endl;
            std::cout << "³������: " << res.percent << "%" << std::endl;
            std::cout << "������: " << res.grade << "/12" << std::endl;
            std::cout << "------------------------------" << std::endl;
        }
    }

    static std::vector<Results> get_subject_result(std::string subject_name) {
        std::vector <Results> all_subject_results; // ������ � ���� ������������ �� ������� ��������
        std::ifstream file;
        file.open(result_file); // �������� ����� � ������������

        if (!file.is_open()) {
            return all_subject_results; // ���������� ������� ������� ���� ���� �� ������� �������
        }
        std::string line; // ����� ��� ������� �����
        while (file) { // ����������� �� ������ ����
            std::string curr_username,curr_subject, curr_test;
            int correct, total, grade;
            double percent;

            if (std::getline(file, line)) {
                curr_username = line; // ������ �������� ����
            }
            if (std::getline(file, line)) {
                curr_subject = line; // ������ �������� �������
            }
            if (std::getline(file, line)) {
                curr_test = line; // ������ �������� ����
            }
            if (std::getline(file, line)) {
                correct = std::stoi(line); // ������������ ������� ���������� �������� � ������ � �����
            }
            if (std::getline(file, line)) {
                total = std::stoi(line); // ������������ �������� ������� �������� � ������ � �����
            }
            if (std::getline(file, line)) {
                percent = std::stod(line); // ������������ % � ������ � ����� (double)
            }
            if (std::getline(file, line)) {
                grade = std::stoi(line); // ������������ ������ � ������ � �����
            }
            std::getline(file, line); // ���������� ��, �� ��������� ����������
            if (curr_subject == subject_name) {
                // ���� ��� ��������, ��������� ����� ��������� � ������ ���� �� �������
                Results result;
                result.username = curr_username;
                result.subject_name = curr_subject;
                result.test_name = curr_test;
                result.correct_answers = correct;
                result.total_questions = total;
                result.percent = percent;
                result.grade = grade;
                all_subject_results.push_back(result); // ������ ��������� �� ������� ��� ���������� ����� �����������

            }
        }
        file.close();
        return all_subject_results;
    }

    static void show_subject_result(std::string subject_name) {
        std::vector<Results> all_subject_result = get_subject_result(subject_name); // �� ���������� �� ���������

        if (all_subject_result.empty()) { // ���� ������ ������ � ������� �� ��������
            std::cout << "���������� �� ��������� " << subject_name << " �� ��������" << std::endl;
        }
        else {
            std::cout << "===== ���������� �� ��������� '" << subject_name << "' ==== = " << std::endl;
            for (const auto& res : all_subject_result) {
                std::cout << "����: " << res.test_name << std::endl;
                std::cout << "����������: " << res.username << std::endl;
                std::cout << "���������� ��������: " << res.correct_answers << "/" << res.total_questions << std::endl;
                std::cout << "³������: " << res.percent << "%" << std::endl;
                std::cout << "������: " << res.grade << "/12" << std::endl;
                std::cout << "------------------------------" << std::endl;
            }
        }
    }

};