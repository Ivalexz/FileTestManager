#include "admin_manage_tests.h"
#include "test_info.h"
#include "test.h"

bool is_subject_in_program(std::string subject_name) { //функція для перевірки існування предмета
    for (const auto& subject : TestInfo::subjects) {
        if (subject.name == subject_name) {
            return true;
        }
    }
    return false;
}

  //функція для перевірки існування певного теста в предметі
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

//   функція для виводу списку всіх предметів
void show_all_subjects() {
    std::cout << "====== Список усіх предметів ======"<<std::endl;
    if (TestInfo::subjects.empty()) {  // якщо предметів ще немає
        std::cout << "Предметів ще немає. Спочатку додайте предмет"<<std::endl;
        return;
    }
    for (const auto& subject : TestInfo::subjects) {
        std::cout << "- " << subject.name << std::endl; //вивід предметів
    }
}

//функція для виводу списку всіх тестів у певному предметі
void show_tests_in_subject(std::string subject_name) {
    std::cout << "====== Тести у категорії '" << subject_name << "' ======"<<std::endl;
    bool is_tests = false; //чи знайдено тести у предметі

    for (const auto& subject : TestInfo::subjects) {
        if (subject.name == subject_name) {
            is_tests = true;
            if (subject.tests.empty()) {
                std::cout << "Тестів для цього предмета ще немає" << std::endl;
                return;
            }

            for (const auto& test : subject.tests) {
                std::cout << "- " << test.test_name << " (" << test.questions.size() << " питань)"<<std::endl;
            }
            break;
        }
    }

    if (!is_tests) {
        std::cout << "Такий предмет не знайдено"<<std::endl;
    }
}

void admin_manage_tests() {  // менюшка дня роботи з тестами (приймається об'єкт для роботи з тестами)
    std::string choice;
    int choices[] = { 1, 2, 3, 4, 5, 6,7};
    Test test; // об'єкт для перевірки наявності предметів

    while (true) {
        std::cout << "====== Управління тестами ======" << std::endl;
        std::cout << "1 - Додати предмет" << std::endl;
        std::cout << "2 - Додати тест" << std::endl;
        std::cout << "3 - Додати питання до існуючого тесту (та задади відповіді)" << std::endl;
        std::cout << "4 - Експортувати у файл" << std::endl;
        std::cout << "5 - Імпортувати з файлу" << std::endl;
        std::cout << "6 - Переглянути предмети та тести" << std::endl;
        std::cout << "7 - Вихід" << std::endl;
        std::cout << "Ваш вибір: ";
        std::cin >> choice;

        int result = ask_user(choices, 7, choice);

        if (result == 1) {
            std::string subject_name;
            std::cout << "Введіть назву предмета: ";
            std::cin.ignore(); // очищає новий рядок перед читанням назви
            std::getline(std::cin, subject_name); // для того, якщо предмет складається з декількох слів
            TestInfo::add_subject(subject_name);
            std::cout << "Предмет додано успішно!"<<std::endl;
        }
        else if (result == 2) {
            if (TestInfo::subjects.empty()) {
                std::cout << "Спочатку додайте хоча б один предмет!" << std::endl;
                continue;
            }

            show_all_subjects();

            std::string subject_name, test_name;
            bool is_subject = false; // для перевірки наявності предмета, до якого додається тест

            while (!is_subject) {
                std::cout << "Введіть назву предмета або '0' для повернення: ";
                std::cin.ignore();
                std::getline(std::cin, subject_name);

                if (subject_name == "0") {
                    break;
                }

                is_subject = is_subject_in_program(subject_name);

                if (!is_subject) {
                    std::cout << "Предмет не знайдено! Спробуйте ще раз"<<std::endl;
                }
            }

            if (!is_subject) {
                continue; // перериває зовнішній цикл меню і повертає користувача назад у головне меню адміна
            }

            std::cout << "Введіть назву нового тесту: ";
            std::getline(std::cin, test_name);

            if (is_test_in_subject(subject_name, test_name)) {
                std::cout << "Тест з назвою '" << test_name << "' вже існує в предметі '" << subject_name << "'!"<<std::endl; //перевірка чи є такий тест
                continue;
            }

            TestInfo::add_test(subject_name, test_name);
            std::cout << "Тест успішно додано!" << std::endl;
        }
        else if (result == 3) {
            if (TestInfo::subjects.empty()) {
                std::cout << "Спочатку додайте хоча б один предмет і тест!"<<std::endl;
                continue; // перериває зовнішній цикл меню і повертає користувача назад у головне меню адміна
            }

            show_all_subjects();

            std::string subject_name, test_name, question_text;
            std::vector<std::string> answers(4); // всього може бути 4 варіанти відповіді
            int correct_answer_index;

            bool is_subject = false;
            while (!is_subject) {
                std::cout << "Введіть назву предмета або '0' для повернення: ";
                std::cin.ignore();
                std::getline(std::cin, subject_name);

                if (subject_name == "0") { // повернення до меню адміна
                    break;
                }

                is_subject = is_subject_in_program(subject_name); //перевірка чи є взагалі такий предмет

                if (!is_subject) {
                    std::cout << "Предмет не знайдено! Спробуйте ще раз"<<std::endl;
                }
            }

            if (!is_subject) {
                continue;
            }

            show_tests_in_subject(subject_name); // показує усі тестування за предметом

            bool is_test = false;
            while (!is_test) {
                std::cout << "Введіть назву тесту або '0' для повернення: ";
                std::getline(std::cin, test_name);

                if (test_name == "0") { // повернення до меню адміна
                    break;
                }

                is_test = is_test_in_subject(subject_name, test_name); // чи є такий тест у предметі

                if (!is_test) {
                    std::cout << "Тест не знайдено! Спробуйте ще раз"<<std::endl;
                }
            }

            if (!is_test) {
                continue;
            }

            std::cout << "Введіть текст питання: ";
            std::getline(std::cin, question_text); // якщо запитання буде з декількох слів

            std::cout << "Введіть варіанти відповіді:"<<std::endl;
            for (int i = 0; i < 4; i++) {
                std::cout << "Варіант " << i + 1 << ": ";
                std::getline(std::cin, answers[i]);
            }

            std::cout << "Індекс правильної відповіді (0-3): ";
            std::cin >> correct_answer_index;

            while (correct_answer_index < 0 || correct_answer_index > 3) {
                std::cout << "Некоректне значення. Спробуйте ще раз (0-3): ";
                std::cin >> correct_answer_index;
            }

            TestInfo::add_question(subject_name, test_name, question_text, answers, correct_answer_index);
            std::cout << "Питання успішно додано!" << std::endl;
        }
        else if (result == 4) {
            if (TestInfo::subjects.empty()) {
                std::cout << "Немає даних для збереження. Спочатку додайте предмети та тести"<<std::endl;
                continue;
            }

            std::string filename;
            std::cout << "Введіть ім'я файлу для збереження: ";
            std::cin.ignore();
            std::getline(std::cin, filename);
            TestInfo::save_tests_to_file(filename);
            std::cout << "Тести успішно збережено у файл: " << filename << std::endl;
        }
        else if (result == 5) {
            std::string filename;
            std::cout << "Введіть ім'я файлу для завантаження: ";
            std::cin.ignore();
            std::getline(std::cin, filename);

            std::vector<TestInfo::TestStruct> all_tests = TestInfo::get_tests_from_file(filename);// усі вигружені тести

            for (const auto& test : all_tests) {  // додає вигружені тести до структури
                bool is_subject = false; //  перевіряє чи є такий предмет
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

                if (!is_subject) { // коли предмета немає, створює новий
                    TestInfo::Subject new_subject;
                    new_subject.name = test.subject;
                    new_subject.tests.push_back(test);
                    TestInfo::subjects.push_back(new_subject);
                }
            }

            std::cout << "Тести успішно завантажено з файлу: " << filename << std::endl;
        }
        else if (result == 6) {
            if (TestInfo::subjects.empty()) {
                std::cout << "Поки що немає жодних предметів або тестів"<<std::endl;
                continue;
            }

            std::cout << "======= Список предметів та тестів ======="<<std::endl;
            for (const auto& subject : TestInfo::subjects) {
                std::cout << "Предмет: " << subject.name << std::endl;

                if (subject.tests.empty()) {
                    std::cout << "Немає тестів для цього предмета"<<std::endl;
                }
                else {
                    for (const auto& test : subject.tests) {
                        std::cout << "  Тест: " << test.test_name << " (" << test.questions.size() << " питань)"<<std::endl;
                    }
                }
                std::cout << std::endl;
            }
        }
        else {
            std::cout << "Вихід з меню..."<<std::endl;
            break;
        }

        std::cout << std::endl;
    }
}