#pragma once
#include <vector>
#include <string>

class TestInfo { // ���� ��� ��������� ���������� ���������� ��� ����
public:
    struct Question { // ��������� ��� ��������
        std::string text;
        std::vector<std::string> answers_variants;
        int correct_answer_index;
    };

    struct TestStruct {// ��������� ��� �����
        std::string subject; // ����� ��������
        std::string test_name; //����� �����
        std::vector<Question> questions;
    };

    struct Subject {//��������� ��� ��������
        std::string name;
        std::vector<TestStruct> tests;
    };

    static std::vector<Subject> subjects;//������ ��������

    // ��� ��������� ��������/�����/�������� ������
    static void add_subject(std::string subject_name);
    static void add_test(std::string subject_name, std::string test_name);
    static void add_question(std::string subject_name, std::string test_name, std::string question_text, std::vector<std::string> answers_variants, int correct_answer_index);

    static void save_tests_to_file(std::string file_name); // ��� ���������� ����� � ����
    static std::vector<TestStruct> get_tests_from_file(std::string file_name); //��� ���������� ����� � �����
    static void get_all_default_questions(); //������� �� ������� �����


};