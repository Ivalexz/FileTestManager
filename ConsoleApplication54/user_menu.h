#pragma once

#include "user.h"
#include "test.h"

// оголошення  функціїйдля того, щоб у інші файли умпортувати хедер файл, а не cpp

void save_test_result(User& user, Test& test); // зберагає результат тесту
bool continue_unfinished_test(User& current_user); // продовжує тест з останнього питання
bool do_test_menu(User& current_user); //  показує менб для виконання тесту
void user_menu(User& current_user);// показує меню користувача
