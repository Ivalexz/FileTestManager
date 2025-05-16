#include <iostream>
#include <fstream>
#include <string> 
#include "test_info.h"

std::vector<TestInfo::Subject> TestInfo::subjects;

void TestInfo::add_subject(std::string subject_name) {
    subjects.push_back(Subject {
        subject_name,
        {}//пустий вектор запитань
        });
}

void TestInfo::add_test(std::string subject_name,std::string test_name) { // створює тест
    for (auto& subject : subjects) {
        if (subject.name == subject_name) {
            for (const auto& test : subject.tests) { // перевіряє чи немає такого тесту
                if (test.test_name == test_name) {
                    return; // такий тест вже існує
                }
            }

            TestStruct new_test;  // створює новий тест та додає його до предмету
            new_test.subject = subject_name;
            new_test.test_name = test_name;
            subject.tests.push_back(new_test);
            return;
        }
    }
    // якщо не знайдено предмет, створює його і додає тест
    add_subject(subject_name);
    add_test(subject_name, test_name);
}

// додає запитання
void TestInfo::add_question(std::string subject_name, std::string test_name, std::string question_text, std::vector<std::string> answers_variants, int correct_answer_index) {
    for (auto& subject : subjects) {
        if (subject.name == subject_name) {
            for (auto& test : subject.tests) {
                if (test.test_name == test_name) {
                    Question new_question; // створює нове запитання
                    new_question.text = question_text;
                    new_question.answers_variants = answers_variants;
                    new_question.correct_answer_index = correct_answer_index;

                    test.questions.push_back(new_question); // додає запитання до тесту
                    return;
                }
            }
        }
    }
}

void TestInfo::save_tests_to_file(std::string file_name) { // для збереження тестів у файл
    std::ofstream file_to_save(file_name);
    for (auto& subject : subjects) {
        file_to_save << subject.name << std::endl;
        for (auto& test : subject.tests) {
            file_to_save << test.test_name << std::endl;
            for (auto& question : test.questions) {
                file_to_save << question.text << std::endl;
                for (auto& answer : question.answers_variants) {
                    file_to_save << answer << std::endl;
                }
                file_to_save << question.correct_answer_index << std::endl;
            }
        }
    }
    file_to_save.close();
}

std::vector<TestInfo::TestStruct> TestInfo::get_tests_from_file(std::string filename) { //для вигруження тестів з файлу
    std::vector<TestStruct> tests;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Не вдалося відкрити файл!" << std::endl; // якщо проблема з відкриттям файлу
        return tests;
    }

    std::string line;
    while (getline(file, line)) {
        TestStruct test;
        test.subject = line;

        if (!getline(file, test.test_name)) { //перевірка чи зчитка з файлу була успішною і без помилок
            break;
        }

        Question question;
        int question_count = 0; // лічильник питань

        while (getline(file, question.text)) {
            if (question.text == "---------------------") { // лінія, яка розділяє тести між собою
                if (!test.questions.empty()) {
                    tests.push_back(test);  // завершено один тест
                    test.questions.clear();
                }
                break;
            }

            question.answers_variants.clear(); //очищення вектора з варіантами відповідей, щоб нові не перемішувались з старими
            for (int i = 0; i < 4; i++) { // проходження по 4 варіантам відповіді
                if (!getline(file, line)) { //перевірка чи зчитка з файлу була успішною і без помилок
                    break;
                }
                question.answers_variants.push_back(line);
            }

            if (!getline(file, line)) break;
            question.correct_answer_index = stoi(line); // перетворення індексу на ціле число

            test.questions.push_back(question);
        }

        if (!file) { //якщо це кінець файлу ( пеервірка відбувається після отримання ліній, які розділюють тести)
            if (!test.questions.empty()) {
                tests.push_back(test); //пушимо усі питання до структури
            }
            break;
        }
    }

    file.close();
    return tests; // повертаємо усі тести
}

void TestInfo::get_all_default_questions() {

    // додає предмети
    add_subject("Математика");
    add_subject("Біологія");

    // додає тести для кожного предмета
    add_test("Математика", "Дискретна математика");
    add_test("Математика", "Математичний аналіз");
    add_test("Біологія", "Ботаніка");
    add_test("Біологія", "Цитологія");

    // Математика — Дискретна математика
    add_question("Математика", "Дискретна математика",
        "Яке з наведених тверджень є правильним для відношення еквівалентності?",
        { "Транзитивне, симетричне та рефлексивне", "Тільки транзитивне", "Тільки симетричне та антирефлексивне", "Ні одне з наведених" }, 0);

    add_question("Математика", "Дискретна математика",
        "Скільки підмножин має множина з 3 елементів?",
        { "3", "6", "8", "4" }, 2);

    add_question("Математика", "Дискретна математика",
        "Що таке граф у теорії графів?",
        { "Послідовність чисел", "Графік функції", "Структура з вершин і ребер", "Формула" }, 2);

    add_question("Математика", "Дискретна математика",
        "Що таке булева алгебра?",
        { "Система чисел", "Система з логічними операціями", "Графік", "Функція" }, 1);

    add_question("Математика", "Дискретна математика",
        "Що є одиницею інформації?",
        { "Байт", "Біт", "Мегабайт", "Символ" }, 1);

    add_question("Математика", "Дискретна математика",
        "Який з логічних елементів реалізує операцію AND?",
        { "Інвертор", "Диз’юнктор", "Кон’юнктор", "Тригер" }, 2);

    // Математика — Математичний аналіз
    add_question("Математика", "Математичний аналіз",
        "Похідна від x^2 дорівнює?",
        { "x", "2x", "x^2", "1" }, 1);

    add_question("Математика", "Математичний аналіз",
        "Площа під графіком функції — це...",
        { "довжина", "об'єм", "інтеграл", "границя" }, 2);

    add_question("Математика", "Математичний аналіз",
        "Що таке границя функції?",
        { "Різниця значень", "Значення функції", "Похідна", "Значення, до якого прямує функція" }, 3);

    add_question("Математика", "Математичний аналіз",
        "Похідна від sin(x) дорівнює?",
        { "sin(x)", "cos(x)", "-cos(x)", "-sin(x)" }, 1);

    add_question("Математика", "Математичний аналіз",
        "Інтеграл від 1/x дорівнює?",
        { "1/x", "ln|x|", "x", "x^2" }, 1);

    add_question("Математика", "Математичний аналіз",
        "Що означає знак ∑ у математиці?",
        { "добуток", "границя", "сума", "інтеграл" }, 2);

    // Біологія — Ботаніка
    add_question("Біологія", "Ботаніка",
        "Яка частина рослини відповідає за фотосинтез?",
        { "Корінь", "Стебло", "Листок", "Квітка" }, 2);

    add_question("Біологія", "Ботаніка",
        "Який орган рослини всмоктує воду?",
        { "Стебло", "Корінь", "Листок", "Насіння" }, 1);

    add_question("Біологія", "Ботаніка",
        "Яка тканина рослин транспортує воду?",
        { "Флоема", "Ксилема", "Меристема", "Епідерма" }, 1);

    add_question("Біологія", "Ботаніка",
        "Що таке фотосинтез?",
        { "Процес дихання", "Процес утворення органічних речовин", "Обмін газів", "Ріст" }, 1);

    add_question("Біологія", "Ботаніка",
        "Яка речовина необхідна для фотосинтезу?",
        { "Кисень", "Азот", "Вуглекислий газ", "Вода" }, 2);

    add_question("Біологія", "Ботаніка",
        "Який пігмент бере участь у фотосинтезі?",
        { "Антоціан", "Каротин", "Хлорофіл", "Гемоглобін" }, 2);

    // Біологія — Цитологія
    add_question("Біологія", "Цитологія",
        "Що є основною одиницею будови живого організму?",
        { "Орган", "Тканина", "Клітина", "Атом" }, 2);

    add_question("Біологія", "Цитологія",
        "Який органоїд відповідає за синтез білків?",
        { "Ядро", "Мітохондрія", "Рибосома", "Вакуоль" }, 2);

    add_question("Біологія", "Цитологія",
        "Що міститься в ядрі клітини?",
        { "Клітинна стінка", "Цитоплазма", "ДНК", "Рибосоми" }, 2);

    add_question("Біологія", "Цитологія",
        "Який органоїд забезпечує енергію клітині?",
        { "Ядро", "Мітохондрія", "Рибосома", "ЕПС" }, 1);

    add_question("Біологія", "Цитологія",
        "Що таке плазматична мембрана?",
        { "Рідина", "Оболонка клітини", "Органоїд", "Фермент" }, 1);

    add_question("Біологія", "Цитологія",
        "Який процес поділу клітини є мітозом?",
        { "Утворення трьох клітин", "Розпад ядра", "Утворення двох ідентичних клітин", "Злиття клітин" }, 2);
}

