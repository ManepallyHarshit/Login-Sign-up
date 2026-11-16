#include "utils.h"
#include <string>
#include <algorithm>
#include <random>
#include <cctype>

using namespace std;

namespace Utils {
    int checkStrength(const string& password) {
        if (password.length() < 7) return 1;

        bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;

        for (char c : password) {
            if (islower(static_cast<unsigned char>(c))) hasLower = true;
            else if (isupper(static_cast<unsigned char>(c))) hasUpper = true;
            else if (isdigit(static_cast<unsigned char>(c))) hasDigit = true;
            else hasSpecial = true;
        }

        int score = hasLower + hasUpper + hasDigit + hasSpecial;
        
        if (score <= 1) return 1;
        if (score == 2) return 2;
        if (score == 3) return 3;
        return 4;
    }

    void generatePassword(string& password, int length) {
        const string lower = "abcdefghijklmnopqrstuvwxyz";
        const string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const string digits = "0123456789";
        const string symbols = "!@#$%^&*()_+-=";
        const string all = lower + upper + digits + symbols;

        password.clear();
        password.reserve(length);

        static mt19937 rng{random_device{}()};
        uniform_int_distribution<size_t> distLower(0, lower.size() - 1);
        uniform_int_distribution<size_t> distUpper(0, upper.size() - 1);
        uniform_int_distribution<size_t> distDigit(0, digits.size() - 1);
        uniform_int_distribution<size_t> distSymbol(0, symbols.size() - 1);
        uniform_int_distribution<size_t> distAll(0, all.size() - 1);

        password += lower[distLower(rng)];
        password += upper[distUpper(rng)];
        password += digits[distDigit(rng)];
        password += symbols[distSymbol(rng)];

        for (int i = 4; i < length; ++i) {
            password += all[distAll(rng)];
        }

        shuffle(password.begin(), password.end(), rng);
    }
}