#pragma once
#include <string>

class Admin { // êëàñ äëÿ çáåðåæåííÿ äàíèõ ïðî àäì³íà
private:
    std::string username;
    std::string password;

public:
    explicit Admin(){}
    explicit Admin(std::string username, std::string password) {
        this->username = username;
        this->password = password;
    }

    void set_password(std::string pass) {
        this->password = pass;
    }
    void set_username(std::string username) {
        this->username = username;
    }

    std::string get_password() {
        return password;
    }
    std::string get_username() {
        return username;
    }
};
