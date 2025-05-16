#pragma once
#include <string>

class invalid_number :std::exception {  // вийняток для розгалужень
private:
	std::string msg;
public:
	invalid_number() {}
	invalid_number(std::string msg) {
		this->msg = msg;
	}
	const char* what() {
		return msg.c_str();
	}
};