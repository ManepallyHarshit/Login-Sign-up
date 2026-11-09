#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "auth.h"
#include "game.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    AuthManager auth;
    GameManager game;
    int choice;
    string username;

    while (true) {
        cout << "\nPassword Auth System: \n1. Register User\n2. Login\n3. Exit\nEnter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                auth.registerUser();
                break;

            case 2:
                if (auth.loginUser(username)) {
                    cout << "Login successful!\n";
                    game.playRPS(username);
                } else {
                    cout << "Login Failed!\n";
                }
                break;

            case 3:
                cout << "Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice!\n";
                break;
        }
    }

    return 0;
}