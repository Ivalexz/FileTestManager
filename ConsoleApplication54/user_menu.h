#pragma once

#include "user.h"
#include "test.h"

// ����������  ����������� ����, ��� � ���� ����� ����������� ����� ����, � �� cpp

void save_test_result(User& user, Test& test); // ������� ��������� �����
bool continue_unfinished_test(User& current_user); // �������� ���� � ���������� �������
bool do_test_menu(User& current_user); //  ������ ���� ��� ��������� �����
void user_menu(User& current_user);// ������ ���� �����������
