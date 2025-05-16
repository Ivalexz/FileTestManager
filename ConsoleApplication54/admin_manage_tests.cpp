#include "admin_manage_tests.h"
#include "test_info.h"
#include "test.h"

bool is_subject_in_program(std::string subject_name) { //������� ��� �������� ��������� ��������
    for (const auto& subject : TestInfo::subjects) {
        if (subject.name == subject_name) {
            return true;
        }
    }
    return false;
}

  //������� ��� �������� ��������� ������� ����� � �������
bool is_test_in_subject(std::string subject_name, std::string test_name) {
    for (const auto& subject : TestInfo::subjects) {
        if (subject.name == subject_name) {
            for (const auto& test : subject.tests) {
                if (test.test_name == test_name) {
                    return true;
                }
            }
            break;
        }
    }
    return false;
}

//   ������� ��� ������ ������ ��� ��������
void show_all_subjects() {
    std::cout << "====== ������ ��� �������� ======"<<std::endl;
    if (TestInfo::subjects.empty()) {  // ���� �������� �� ����
        std::cout << "�������� �� ����. �������� ������� �������"<<std::endl;
        return;
    }
    for (const auto& subject : TestInfo::subjects) {
        std::cout << "- " << subject.name << std::endl; //���� ��������
    }
}

//������� ��� ������ ������ ��� ����� � ������� �������
void show_tests_in_subject(std::string subject_name) {
    std::cout << "====== ����� � ������� '" << subject_name << "' ======"<<std::endl;
    bool is_tests = false; //�� �������� ����� � �������

    for (const auto& subject : TestInfo::subjects) {
        if (subject.name == subject_name) {
            is_tests = true;
            if (subject.tests.empty()) {
                std::cout << "����� ��� ����� �������� �� ����" << std::endl;
                return;
            }

            for (const auto& test : subject.tests) {
                std::cout << "- " << test.test_name << " (" << test.questions.size() << " ������)"<<std::endl;
            }
            break;
        }
    }

    if (!is_tests) {
        std::cout << "����� ������� �� ��������"<<std::endl;
    }
}

void admin_manage_tests() {  // ������� ��� ������ � ������� (���������� ��'��� ��� ������ � �������)
    std::string choice;
    int choices[] = { 1, 2, 3, 4, 5, 6,7};
    Test test; // ��'��� ��� �������� �������� ��������

    while (true) {
        std::cout << "====== ��������� ������� ======" << std::endl;
        std::cout << "1 - ������ �������" << std::endl;
        std::cout << "2 - ������ ����" << std::endl;
        std::cout << "3 - ������ ������� �� ��������� ����� (�� ������ ������)" << std::endl;
        std::cout << "4 - ������������ � ����" << std::endl;
        std::cout << "5 - ����������� � �����" << std::endl;
        std::cout << "6 - ����������� �������� �� �����" << std::endl;
        std::cout << "7 - �����" << std::endl;
        std::cout << "��� ����: ";
        std::cin >> choice;

        int result = ask_user(choices, 7, choice);

        if (result == 1) {
            std::string subject_name;
            std::cout << "������ ����� ��������: ";
            std::cin.ignore(); // ����� ����� ����� ����� �������� �����
            std::getline(std::cin, subject_name); // ��� ����, ���� ������� ���������� � �������� ���
            TestInfo::add_subject(subject_name);
            std::cout << "������� ������ ������!"<<std::endl;
        }
        else if (result == 2) {
            if (TestInfo::subjects.empty()) {
                std::cout << "�������� ������� ���� � ���� �������!" << std::endl;
                continue;
            }

            show_all_subjects();

            std::string subject_name, test_name;
            bool is_subject = false; // ��� �������� �������� ��������, �� ����� �������� ����

            while (!is_subject) {
                std::cout << "������ ����� �������� ��� '0' ��� ����������: ";
                std::cin.ignore();
                std::getline(std::cin, subject_name);

                if (subject_name == "0") {
                    break;
                }

                is_subject = is_subject_in_program(subject_name);

                if (!is_subject) {
                    std::cout << "������� �� ��������! ��������� �� ���"<<std::endl;
                }
            }

            if (!is_subject) {
                continue; // �������� ������� ���� ���� � ������� ����������� ����� � ������� ���� �����
            }

            std::cout << "������ ����� ������ �����: ";
            std::getline(std::cin, test_name);

            if (is_test_in_subject(subject_name, test_name)) {
                std::cout << "���� � ������ '" << test_name << "' ��� ���� � ������� '" << subject_name << "'!"<<std::endl; //�������� �� � ����� ����
                continue;
            }

            TestInfo::add_test(subject_name, test_name);
            std::cout << "���� ������ ������!" << std::endl;
        }
        else if (result == 3) {
            if (TestInfo::subjects.empty()) {
                std::cout << "�������� ������� ���� � ���� ������� � ����!"<<std::endl;
                continue; // �������� ������� ���� ���� � ������� ����������� ����� � ������� ���� �����
            }

            show_all_subjects();

            std::string subject_name, test_name, question_text;
            std::vector<std::string> answers(4); // ������ ���� ���� 4 ������� ������
            int correct_answer_index;

            bool is_subject = false;
            while (!is_subject) {
                std::cout << "������ ����� �������� ��� '0' ��� ����������: ";
                std::cin.ignore();
                std::getline(std::cin, subject_name);

                if (subject_name == "0") { // ���������� �� ���� �����
                    break;
                }

                is_subject = is_subject_in_program(subject_name); //�������� �� � ������ ����� �������

                if (!is_subject) {
                    std::cout << "������� �� ��������! ��������� �� ���"<<std::endl;
                }
            }

            if (!is_subject) {
                continue;
            }

            show_tests_in_subject(subject_name); // ������ �� ���������� �� ���������

            bool is_test = false;
            while (!is_test) {
                std::cout << "������ ����� ����� ��� '0' ��� ����������: ";
                std::getline(std::cin, test_name);

                if (test_name == "0") { // ���������� �� ���� �����
                    break;
                }

                is_test = is_test_in_subject(subject_name, test_name); // �� � ����� ���� � �������

                if (!is_test) {
                    std::cout << "���� �� ��������! ��������� �� ���"<<std::endl;
                }
            }

            if (!is_test) {
                continue;
            }

            std::cout << "������ ����� �������: ";
            std::getline(std::cin, question_text); // ���� ��������� ���� � �������� ���

            std::cout << "������ ������� ������:"<<std::endl;
            for (int i = 0; i < 4; i++) {
                std::cout << "������ " << i + 1 << ": ";
                std::getline(std::cin, answers[i]);
            }

            std::cout << "������ ��������� ������ (0-3): ";
            std::cin >> correct_answer_index;

            while (correct_answer_index < 0 || correct_answer_index > 3) {
                std::cout << "���������� ��������. ��������� �� ��� (0-3): ";
                std::cin >> correct_answer_index;
            }

            TestInfo::add_question(subject_name, test_name, question_text, answers, correct_answer_index);
            std::cout << "������� ������ ������!" << std::endl;
        }
        else if (result == 4) {
            if (TestInfo::subjects.empty()) {
                std::cout << "���� ����� ��� ����������. �������� ������� �������� �� �����"<<std::endl;
                continue;
            }

            std::string filename;
            std::cout << "������ ��'� ����� ��� ����������: ";
            std::cin.ignore();
            std::getline(std::cin, filename);
            TestInfo::save_tests_to_file(filename);
            std::cout << "����� ������ ��������� � ����: " << filename << std::endl;
        }
        else if (result == 5) {
            std::string filename;
            std::cout << "������ ��'� ����� ��� ������������: ";
            std::cin.ignore();
            std::getline(std::cin, filename);

            std::vector<TestInfo::TestStruct> all_tests = TestInfo::get_tests_from_file(filename);// �� �������� �����

            for (const auto& test : all_tests) {  // ���� �������� ����� �� ���������
                bool is_subject = false; //  �������� �� � ����� �������
                for (auto& subject : TestInfo::subjects) {
                    if (subject.name == test.subject) {
                        is_subject = true;
                        bool is_test = false;
                        for (const auto& existing_test : subject.tests) {
                            if (existing_test.test_name == test.test_name) {
                                is_test = true;
                                break;
                            }
                        }

                        if (!is_test) {
                            subject.tests.push_back(test);
                        }
                        break;
                    }
                }

                if (!is_subject) { // ���� �������� ����, ������� �����
                    TestInfo::Subject new_subject;
                    new_subject.name = test.subject;
                    new_subject.tests.push_back(test);
                    TestInfo::subjects.push_back(new_subject);
                }
            }

            std::cout << "����� ������ ����������� � �����: " << filename << std::endl;
        }
        else if (result == 6) {
            if (TestInfo::subjects.empty()) {
                std::cout << "���� �� ���� ������ �������� ��� �����"<<std::endl;
                continue;
            }

            std::cout << "======= ������ �������� �� ����� ======="<<std::endl;
            for (const auto& subject : TestInfo::subjects) {
                std::cout << "�������: " << subject.name << std::endl;

                if (subject.tests.empty()) {
                    std::cout << "���� ����� ��� ����� ��������"<<std::endl;
                }
                else {
                    for (const auto& test : subject.tests) {
                        std::cout << "  ����: " << test.test_name << " (" << test.questions.size() << " ������)"<<std::endl;
                    }
                }
                std::cout << std::endl;
            }
        }
        else {
            std::cout << "����� � ����..."<<std::endl;
            break;
        }

        std::cout << std::endl;
    }
}