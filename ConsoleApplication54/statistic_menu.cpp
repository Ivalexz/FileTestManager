#include "statistic_menu.h"
#include "exception_function.h"
#include "test.h"

bool get_test_res(TestResult test_result) {
    std::string users_choice;
    std::cout << "������� �������, �� ����� ����������� ����������: " << std::endl;

    std::vector<std::string> subjects = Test::get_subject_list(); // ������ �������� (������)
    int count_subjects = subjects.size(); // ������� ��������
    int* sub_choices = new int[count_subjects];  // ��������� ����� ��� ������ ��������

    for (size_t i = 0; i < count_subjects; i++) {
        std::cout << i + 1 << " - " << subjects[i] << std::endl; // ���� ��������
        sub_choices[i] = i + 1; // ��������� ������� ��������
    }
    std::cout << "��� ����: ";
    std::cin >> users_choice;

    int sub_result = ask_user(sub_choices, 2, users_choice); // ������� ����� � ���������, �� ������� �� ���� ����������� �� ������� �������
    delete[] sub_choices;  // ��������� ���`��

    if (sub_result == -1) {
        return false;  // ���� ���� ���� �� ��� 
    }
    int subject_index = sub_result - 1;  // ���������� ������� ��������� ��������

    std::cout << "������� �����: " << std::endl;

    std::vector<std::string> tests = Test::get_test_list(subject_index); // ������ ����� (������)
    int test_count = tests.size();  //������� �����
    int* test_choices = new int[test_count];  // ��������� ����� ��� ������ �����

    for (int i = 0; i < test_count; i++) {
        test_choices[i] = i + 1; // ��������� ������� ��������
        std::cout << i + 1 << " - " <<tests[i] << std::endl;  // ���� ��� ��������� �����
    }

    std::cout << "������ ����: ";
    std::cin >> users_choice;

    int test_res = ask_user(test_choices, test_count, users_choice);  // ������� ����� � ���������, �� ������� �� ���� ����������� �� ������� �������
    delete[] test_choices; // ��������� ���'���

    if (test_res == -1) {
        return false; // ���� ���� ���� �� ��� 
    }
    int test_index = test_res - 1;  // ���������� ������� ��������� ����������

    test_result.show_test_result(subjects[subject_index], tests[test_index]); //������ ���������� ���������
    return true;
}

bool get_sub_res(TestResult test_result) {
    std::string users_choice;
    std::cout << "������� �������, �� ����� ����������� ����������: " << std::endl;

    std::vector<std::string> subjects = Test::get_subject_list();
    int count_subjects = subjects.size();  // ������� ��������
    int* sub_choices = new int[count_subjects];  // ��������� ����� ��� ������ ��������

    for (size_t i = 0; i < count_subjects; i++) {
        std::cout << i + 1 << " - " << subjects[i] << std::endl; // ���� ��������
        sub_choices[i] = i + 1; // ��������� ������� ��������
    }
    std::cout << "��� ����: ";
    std::cin >> users_choice;

    int sub_result = ask_user(sub_choices, 2, users_choice); // ������� ����� � ���������, �� ������� �� ���� ����������� �� ������� �������
    delete[] sub_choices;  // ��������� ���`��

    if (sub_result == -1) {
        return false;  // ���� ���� ���� �� ��� 
    }
    int subject_index = sub_result - 1;  // ���������� ������� ��������� ��������

    test_result.show_subject_result(subjects[subject_index]); // ������ ���������� �� ����������
    return true;
}

bool statistic_menu(TestResult test_result) {
    std::string choice;
    int choices[] = { 1, 2, 3, 4 };
    while (true) {
        std::cout << "====== �������� ���������� ======" << std::endl;
        std::cout << "1 - ����������� ���������� �� ����������" << std::endl;
        std::cout << "2 - ����������� ���������� �� �������" << std::endl;
        std::cout << "3 - ����������� ���������� �� �������������" << std::endl;
        std::cout << "4 - �����" << std::endl;
        std::cout << "��� ����: ";
        std::cin >> choice;

        int result = ask_user(choices, 4, choice);

        if (result == 1) {
            if (!get_sub_res(test_result)) {
                return false;
            }
        }
        else if (result == 2) {
            if (!get_test_res(test_result)) {
                return false;
            }
        }
        else if (result == 3) {
            std::string username;
            std::cout << "������ ���� �����������, ���������� ����� ������ �����������: " << std::endl;
            std::cin >> username;
            test_result.show_user_results(username);
        }
        else {
            break;
        }

    }
}