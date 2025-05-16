#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class TestFileGetterAndSaver{ // ���� ��� ������� ����� � ����� �� �� ����������
public:
      //������������ ����� � ����� � ������� ������ (��������� �����������)
    static bool read_tests_from_file(const std::string& filename,
        std::string**& subjects, int& subject_count, // ����� ���� ��������
        std::string***& tests, int* test_counts, // ����� ����� � ������� �������
        std::string****& questions, int** question_counts, // ��������� � ������� ����
        std::string*****& answers, int*** answer_counts, // ������ �� ������� ���������
        int***& correct_answers // �������� ������ �� ������� ���������
    );

    //������� > ����� > ��������� > ������ >�������� �������

    static bool save_tests_to_file(const std::string& filename, //���������� ����� � ���� � ��������� ������
        std::string** subjects, int subject_count,
        std::string*** tests, int* test_counts,
        std::string**** questions, int** question_counts,
        std::string***** answers, int*** answer_counts,
        int*** correct_answers
    );

    static bool save_default_tests_to_file(const std::string& filename);  // ������� ��� ��������� ����������� ����� � ����
};