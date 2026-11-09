#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
    int checkStrength(const std::string& password);
    void generatePassword(std::string& password, int length);
}

#endif