#include "auth.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

bool AuthManager::usernameExists(const string& username) const {
    ifstream file(USER_DATA_FILE);
    if (!file.is_open()) return false;

    string savedUser, savedPass;
    while (file >> savedUser >> savedPass) {
        if (username == savedUser) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void AuthManager::registerUser() {
    string username, password;
    int choice;

    cout << "\nEnter Username: ";
    cin >> username;

    if (usernameExists(username)) {
        cerr << "Error: Username '" << username << "' already exists!\n";
        return;
    }

    ofstream file(USER_DATA_FILE, ios::app);
    if (!file.is_open()) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    bool validChoice = false;
    while (!validChoice) {
        cout << "\n1. Enter your own password\n2. Generate strong password\nChoice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter 1 or 2.\n";
            continue;
        }
        if (choice == 1 || choice == 2) {
            validChoice = true;
        } else {
            cout << "Invalid choice! Please enter 1 or 2.\n";
        }
    }

    if (choice == 1) {
        do {
            cout << "Enter Password: ";
            cin >> password;

            if (password.length() <= 6) {
                cout << "Password very weak and has less characters.\nTry again!\n";
            }
        } while (password.length() <= 6);

        int strength = Utils::checkStrength(password);

        if (strength == 1) {
            cout << "Password strength: WEAK — Please choose a stronger password.\n\n";
            file.close();
            return;
        } else if (strength == 2) {
            cout << "Password strength: GOOD\n";
        } else {
            cout << "Password strength: EXCELLENT\n";
        }
    } else if (choice == 2) {
        int len = 0;
        constexpr int kMinPasswordLength = 7;
        constexpr int kMaxPasswordLength = 128;
        while (len < kMinPasswordLength || len > kMaxPasswordLength) {
            cout << "Enter the length of your password (" << kMinPasswordLength << "-" << kMaxPasswordLength << "): ";
            cin >> len;
            if (len < kMinPasswordLength) {
                cout << "Your password has very few characters.\n";
            } else if (len > kMaxPasswordLength) {
                cout << "Password length too large. Maximum is " << kMaxPasswordLength << " characters.\n";
            }
        }
        Utils::generatePassword(password, len);
        cout << "Generated Password: " << password << "\n";
    }

    file << username << " " << password << "\n";
    file.close();
    cout << "\nUser Registered Successfully!\n";
}

bool AuthManager::loginUser(string& username) const {
    string password;

    cout << "\nEnter Username: ";
    cin >> username;
    cout << "\nEnter Password: ";
    cin >> password;

    ifstream file(USER_DATA_FILE);
    if (!file.is_open()) {
        cerr << "No users registered yet!\n";
        return false;
    }

    string savedUser, savedPass;
    while (file >> savedUser >> savedPass) {
        if (username == savedUser && password == savedPass) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}