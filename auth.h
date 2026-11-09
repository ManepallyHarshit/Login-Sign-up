#ifndef AUTH_H
#define AUTH_H

#include <string>

class AuthManager {
private:
    static constexpr const char* USER_DATA_FILE = "userdata.txt";
    bool usernameExists(const std::string& username) const;

public:
    void registerUser();
    bool loginUser(std::string& username) const;
};

#endif