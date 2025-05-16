#include "statistic_menu.h"
#include "exception_function.h"
#include "test.h"

bool get_test_res(TestResult test_result) {
    std::string users_choice;
    std::cout << "Виберіть предмет, по якому проводиться тестування: " << std::endl;

    std::vector<std::string> subjects = Test::get_subject_list(); // список предметів (вектор)
    int count_subjects = subjects.size(); // кількість предметів
    int* sub_choices = new int[count_subjects];  // динамічний масив для вибору предметів

    for (size_t i = 0; i < count_subjects; i++) {
        std::cout << i + 1 << " - " << subjects[i] << std::endl; // вивід предметів
        sub_choices[i] = i + 1; // зберігання варіантів відповідей
    }
    std::cout << "Ваш вибір: ";
    std::cin >> users_choice;

    int sub_result = ask_user(sub_choices, 2, users_choice); // передаю масив з варіантами, їх кількість та вибір користувача на обробку помилок
    delete[] sub_choices;  // звільнення пам`яті

    if (sub_result == -1) {
        return false;  // якщо щось пішло не так 
    }
    int subject_index = sub_result - 1;  // визначення індексу вибраного предмета

    std::cout << "Доступні тести: " << std::endl;

    std::vector<std::string> tests = Test::get_test_list(subject_index); // список тестів (вектор)
    int test_count = tests.size();  //кількість тестів
    int* test_choices = new int[test_count];  // динамічний масив для вибору тестів

    for (int i = 0; i < test_count; i++) {
        test_choices[i] = i + 1; // зберігання варіантів відповідей
        std::cout << i + 1 << " - " <<tests[i] << std::endl;  // вивід усіх доступних тестів
    }

    std::cout << "Оберіть тест: ";
    std::cin >> users_choice;

    int test_res = ask_user(test_choices, test_count, users_choice);  // передаю масив з варіантами, їх кількість та вибір користувача на обробку помилок
    delete[] test_choices; // звільняємо пам'ять

    if (test_res == -1) {
        return false; // якщо щось пішло не так 
    }
    int test_index = test_res - 1;  // визначення індексу вибраного тестування

    test_result.show_test_result(subjects[subject_index], tests[test_index]); //показує результати тестувань
    return true;
}

bool get_sub_res(TestResult test_result) {
    std::string users_choice;
    std::cout << "Виберіть предмет, по якому проводиться тестування: " << std::endl;

    std::vector<std::string> subjects = Test::get_subject_list();
    int count_subjects = subjects.size();  // кількість предметів
    int* sub_choices = new int[count_subjects];  // динамічний масив для вибору предметів

    for (size_t i = 0; i < count_subjects; i++) {
        std::cout << i + 1 << " - " << subjects[i] << std::endl; // вивід предметів
        sub_choices[i] = i + 1; // зберігання варіантів відповідей
    }
    std::cout << "Ваш вибір: ";
    std::cin >> users_choice;

    int sub_result = ask_user(sub_choices, 2, users_choice); // передаю масив з варіантами, їх кількість та вибір користувача на обробку помилок
    delete[] sub_choices;  // звільнення пам`яті

    if (sub_result == -1) {
        return false;  // якщо щось пішло не так 
    }
    int subject_index = sub_result - 1;  // визначення індексу вибраного предмета

    test_result.show_subject_result(subjects[subject_index]); // показує результати за предметами
    return true;
}

bool statistic_menu(TestResult test_result) {
    std::string choice;
    int choices[] = { 1, 2, 3, 4 };
    while (true) {
        std::cout << "====== Перегляд статистики ======" << std::endl;
        std::cout << "1 - Переглянути результати за предметами" << std::endl;
        std::cout << "2 - Переглянути результати за тестами" << std::endl;
        std::cout << "3 - Переглянути результати за користувачами" << std::endl;
        std::cout << "4 - Вихід" << std::endl;
        std::cout << "Ваш вибір: ";
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
            std::cout << "Введіть логін користувача, результати якого хочете переглянути: " << std::endl;
            std::cin >> username;
            test_result.show_user_results(username);
        }
        else {
            break;
        }

    }
}