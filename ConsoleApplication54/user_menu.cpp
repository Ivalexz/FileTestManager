#include "test.h"
#include "user.h"
#include "user_menu.h"
#include "test_result.h"
#include "exception_function.h"
#include "test_progress.h"
#include <iostream>

void save_test_result(User& user, Test& test) { //  ���������� ���������� ���������� ���� ���� �����������
    if (!test.get_is_done()) {  // �������� �� ���������� �����
        std::cout << "�������: ���� �� ���������, ��������� �������� ���������" << std::endl;
        return;
    }

    std::string subject_name = test.get_subject_name(); // ��`� ��������, � ����� ����������� ����������

    //���������� ���������� ����������
    if (TestResult::save_result_to_file(user.get_username(), subject_name, test.get_name(), test.get_correct_answers(), test.get_total_questions())) {
        std::cout << "��������� ������ ���������!" << std::endl;
    }
    else {
        std::cout << "�������: �� ������� �������� ���������" << std::endl;
    }
}

bool continue_unfinished_test(User& current_user) { //������� ��� ����������� ������������� �����
    // ������ ������ ������������ ����� ������ �����������
    std::vector<UnfinishedTest> unfinished_tests = TestProgress::get_unfinished_tests(current_user.get_username());

    if (unfinished_tests.empty()) {  // �������� �� ���������� ����� �����������
        std::cout << "� ��� ���� ������������ �����" << std::endl;
        return false;
    }

    int* unfinished_tests_choices = new int[unfinished_tests.size()];  // ��������� ����� ��� ������ ������������ �����

    std::cout << "���� ���������� �����: " << std::endl;
    for (size_t i = 0; i < unfinished_tests.size(); i++) {
        unfinished_tests_choices[i] = i + 1;
        UnfinishedTest test = unfinished_tests[i];

        //���������� ��'��� ����� ��� ��������� ���������� ��� �����
        Test tmp_test(test.subject_index, test.test_index);

        std::cout << i + 1 << " - " << tmp_test.get_subject_name() << " - " << tmp_test.get_name();
        std::cout << " (�������: " << test.last_answered_question << "/" << tmp_test.get_total_questions() << ")" << std::endl;
    }

    std::string users_choice;

    std::cout << std::endl << "������� ���� ��� ����������� (��� 0 ��� ����������): ";
    std::cin >> users_choice;

    if (users_choice == "0") {  // ������� �� �����
        delete[] unfinished_tests_choices;  // ��������� ���`��
        return false;
    }

    int unfinished_tests_result = ask_user(unfinished_tests_choices, unfinished_tests.size(), users_choice); // ������� ����� � ���������, �� ������� �� ���� ����������� �� ������� �������
    delete[] unfinished_tests_choices;  // ��������� ���`��

    if (unfinished_tests_result == -1) {// ���� ���� ���� �� ���
        return false;
    }

    const UnfinishedTest& selected_test_index = unfinished_tests[unfinished_tests_result - 1]; // ������ ��������� ������������� �����

    Test current_test(  // ��������� ����� � ���������� ���������
        selected_test_index.subject_index,
        selected_test_index.test_index,
        selected_test_index.correct_answers,
        selected_test_index.last_answered_question,
        current_user.get_username()
    );

    bool test_completed = current_test.run(); // ������ �����

    if (test_completed) {
        save_test_result(current_user, current_test);  // ���������� ���������� ���� ��� ��
        TestResult::show_result_for_test_end(
            current_user.get_username(),
            current_test.get_subject_name(),
            current_test.get_name()
        ); // ���� ���������� ����������
        return true;
    }
    return false;
}

bool do_test_menu(User& current_user) { // ���� ��� ��������� �����
    std::string users_choice;
    std::cout << "������� ������� ��� ����������: " << std::endl;

    std::vector<std::string> subjects = Test::get_subject_list(); // ������ ��������
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

    std::cout << "������� �����: " << std::endl;

    std::vector<std::string> tests = Test::get_test_list(subject_index); // ������ ����� ��� ��������� ��������
    int test_count = tests.size();  //������� �����
    int* test_choices = new int[test_count];  // ��������� ����� ��� ������ �����

    for (int i = 0; i < test_count; i++) {
        test_choices[i] = i + 1; // ��������� ������� ��������
        std::cout << i + 1 << " - " << tests[i] << std::endl;  // ���� ��� ��������� �����
    }

    std::cout << "������ ����: ";
    std::cin >> users_choice;

    int test_result = ask_user(test_choices, test_count, users_choice);  // ������� ����� � ���������, �� ������� �� ���� ����������� �� ������� �������
    delete[] test_choices; // ��������� ���'���

    if (test_result == -1) {
        return false; // ���� ���� ���� �� ��� 
    }
    int test_index = test_result - 1;  // ���������� ������� ��������� ����������

    Test current_test(subject_index, test_index); // ����������� ��������� �����
    current_test.set_username(current_user.get_username()); // ������������ ��'� �����������
    bool test_completed = current_test.run();  // �� �������� ����

    if (test_completed) {
        save_test_result(current_user, current_test);  // ���� ���� ��������, ��������� ���������
        TestResult::show_result_for_test_end(
            current_user.get_username(),
            current_test.get_subject_name(),
            current_test.get_name()
        ); // ���� ���������� ����������
        return true;
    }
    return false;  // ���� ���� �� ��� ����������
}

void user_menu(User& current_user) { // ���� �����������
    std::string users_choice;
    bool continue_menu = true;  // ����� ��� ����������� ��������� ����

    while (continue_menu) {
        std::cout << "=== ���� ����������� ===" << std::endl;
        std::cout << "1 - ����������� �������� ���������� ����������" << std::endl;
        std::cout << "2 - ������ ���� ����������" << std::endl;
        std::cout << "3 - ���������� ������������ ����" << std::endl;
        std::cout << "4 - ����� � ��������" << std::endl;
        std::cout << "��� ����: ";
        std::cin >> users_choice;

        int choices[4] = { 1, 2, 3, 4 };  // ����� � ��������� ������
        int result = ask_user(choices, 4, users_choice);  // ������� ����� � ���������, �� ������� �� ���� ����������� �� ������� �������

        switch (result) {
        case 1:
            TestResult::show_user_results(current_user.get_username());  // ���� ����� �����
            break;
        case 2:
            if (!do_test_menu(current_user)) {  // �������� ���������� �������
                std::cout << "���������� �� ���� �����������..." << std::endl;
            }
            break;
        case 3:
            if (!continue_unfinished_test(current_user)) { // �������� ���������� �������
                std::cout << "���������� �� ���� �����������..." << std::endl;
            }
            break;
        case 4:
            std::cout << "����� � ��������..." << std::endl;   // ����� � �������
            continue_menu = false;
            break;
        }
    }
}
