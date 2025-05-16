#include "test.h"
#include "user.h"
#include "user_menu.h"
#include "test_result.h"
#include "exception_function.h"
#include "test_progress.h"
#include <iostream>

void save_test_result(User& user, Test& test) { //  збереження результату тестування після його проходження
    if (!test.get_is_done()) {  // перевірка на завершення тесту
        std::cout << "Помилка: Тест не завершено, неможливо зберегти результат" << std::endl;
        return;
    }

    std::string subject_name = test.get_subject_name(); // ім`я предмету, з якого проводилось тестування

    //збереження результату тестування
    if (TestResult::save_result_to_file(user.get_username(), subject_name, test.get_name(), test.get_correct_answers(), test.get_total_questions())) {
        std::cout << "Результат успішно збережено!" << std::endl;
    }
    else {
        std::cout << "Помилка: Не вдалося зберегти результат" << std::endl;
    }
}

bool continue_unfinished_test(User& current_user) { //функція для продовження незавершеного тесту
    // дістаємо вектор незавершених тестів даного користувача
    std::vector<UnfinishedTest> unfinished_tests = TestProgress::get_unfinished_tests(current_user.get_username());

    if (unfinished_tests.empty()) {  // перевірка на незавершені тести користувача
        std::cout << "У вас немає незавершених тестів" << std::endl;
        return false;
    }

    int* unfinished_tests_choices = new int[unfinished_tests.size()];  // динамічний масив для вибору незавершених тестів

    std::cout << "Ваші незавершені тести: " << std::endl;
    for (size_t i = 0; i < unfinished_tests.size(); i++) {
        unfinished_tests_choices[i] = i + 1;
        UnfinishedTest test = unfinished_tests[i];

        //тимчасовий об'єкт тесту для отримання інформації про назви
        Test tmp_test(test.subject_index, test.test_index);

        std::cout << i + 1 << " - " << tmp_test.get_subject_name() << " - " << tmp_test.get_name();
        std::cout << " (Прогрес: " << test.last_answered_question << "/" << tmp_test.get_total_questions() << ")" << std::endl;
    }

    std::string users_choice;

    std::cout << std::endl << "Виберіть тест для продовження (або 0 для повернення): ";
    std::cin >> users_choice;

    if (users_choice == "0") {  // первірка на вихід
        delete[] unfinished_tests_choices;  // звільнення пам`яті
        return false;
    }

    int unfinished_tests_result = ask_user(unfinished_tests_choices, unfinished_tests.size(), users_choice); // передаю масив з варіантами, їх кількість та вибір користувача на обробку помилок
    delete[] unfinished_tests_choices;  // звільнення пам`яті

    if (unfinished_tests_result == -1) {// якщо щось пішло не так
        return false;
    }

    const UnfinishedTest& selected_test_index = unfinished_tests[unfinished_tests_result - 1]; // індекс вибраного незавершеного тесту

    Test current_test(  // створення теста з збереженим прогресом
        selected_test_index.subject_index,
        selected_test_index.test_index,
        selected_test_index.correct_answers,
        selected_test_index.last_answered_question,
        current_user.get_username()
    );

    bool test_completed = current_test.run(); // запуск тесту

    if (test_completed) {
        save_test_result(current_user, current_test);  // збереження результатів якщо все ок
        TestResult::show_result_for_test_end(
            current_user.get_username(),
            current_test.get_subject_name(),
            current_test.get_name()
        ); // вивід результату тестування
        return true;
    }
    return false;
}

bool do_test_menu(User& current_user) { // меню для виконання тесту
    std::string users_choice;
    std::cout << "Виберіть предмет для тестування: " << std::endl;

    std::vector<std::string> subjects = Test::get_subject_list(); // список предметів
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

    std::cout << "Доступні тести: " << std::endl;

    std::vector<std::string> tests = Test::get_test_list(subject_index); // список тестів для вибраного предмета
    int test_count = tests.size();  //кількість тестів
    int* test_choices = new int[test_count];  // динамічний масив для вибору тестів

    for (int i = 0; i < test_count; i++) {
        test_choices[i] = i + 1; // зберігання варіантів відповідей
        std::cout << i + 1 << " - " << tests[i] << std::endl;  // вивід усіх доступних тестів
    }

    std::cout << "Оберіть тест: ";
    std::cin >> users_choice;

    int test_result = ask_user(test_choices, test_count, users_choice);  // передаю масив з варіантами, їх кількість та вибір користувача на обробку помилок
    delete[] test_choices; // звільняємо пам'ять

    if (test_result == -1) {
        return false; // якщо щось пішло не так 
    }
    int test_index = test_result - 1;  // визначення індексу вибраного тестування

    Test current_test(subject_index, test_index); // ініціалізація вибраного тесту
    current_test.set_username(current_user.get_username()); // встановлюємо ім'я користувача
    bool test_completed = current_test.run();  // чи виконано тест

    if (test_completed) {
        save_test_result(current_user, current_test);  // якщо тест виконано, зберегаємо результат
        TestResult::show_result_for_test_end(
            current_user.get_username(),
            current_test.get_subject_name(),
            current_test.get_name()
        ); // вивід результату тестування
        return true;
    }
    return false;  // якщо тест не був завершений
}

void user_menu(User& current_user) { // меню користувача
    std::string users_choice;
    bool continue_menu = true;  // змінна для продовження виконання меню

    while (continue_menu) {
        std::cout << "=== Меню користувача ===" << std::endl;
        std::cout << "1 - Переглянути попередні результати тестування" << std::endl;
        std::cout << "2 - Пройти нове тестування" << std::endl;
        std::cout << "3 - Продовжити незавершений тест" << std::endl;
        std::cout << "4 - Вийти з аккаунту" << std::endl;
        std::cout << "Ваш вибір: ";
        std::cin >> users_choice;

        int choices[4] = { 1, 2, 3, 4 };  // масив з варіантами відповіді
        int result = ask_user(choices, 4, users_choice);  // передаю масив з варіантами, їх кількість та вибір користувача на обробку помилок

        switch (result) {
        case 1:
            TestResult::show_user_results(current_user.get_username());  // вивід історії тестів
            break;
        case 2:
            if (!do_test_menu(current_user)) {  // перевірка результату функції
                std::cout << "Повернення до меню користувача..." << std::endl;
            }
            break;
        case 3:
            if (!continue_unfinished_test(current_user)) { // перевірка результату функції
                std::cout << "Повернення до меню користувача..." << std::endl;
            }
            break;
        case 4:
            std::cout << "Вихід з аккаунту..." << std::endl;   // вихід з аккунту
            continue_menu = false;
            break;
        }
    }
}
