#pragma once
#include <string>
#include <iostream>

class User { // клас для обробки інформації про користувача
private:
	std::string full_name, address, phone, username, password;
public:
	static const std::string users_file; // статична константа для назви файлу

	explicit User() {}
	explicit User(std::string full_name, std::string address, std::string phone, std::string username, std::string password) {
		this->full_name = full_name;
		this->address = address;
		this->phone = phone;
		this->username = username;
		this->password = password;
	}

	void set_full_name(std::string name) {
		full_name = name;
	}

	void set_address(std::string addr) {
		address = addr;
	}

	void set_phone(std::string ph) {
		phone = ph;
	}

	void set_username(std::string user) {
		username = user;
	}

	void set_password(std::string pass) {
		password = pass;
	}

	std::string get_full_name() const {
		return full_name;
	}

	std::string get_address() const {
		return address;
	}

	std::string get_phone() const {
		return phone;
	}

	std::string get_username() const {
		return username;
	}

	std::string get_password() const {
		return password;
	}

};