#include "game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>

using namespace std;

struct Score {
    int wins = 0, losses = 0, draws = 0;
    bool isZero() const { return wins == 0 && losses == 0 && draws == 0; }
    void reset() { wins = losses = draws = 0; }
};

string GameManager::getScoreFilename(const string& username) {
    return username + "-score.txt";
}

void GameManager::loadScore(const string& username, Score& score) {
    string filename = getScoreFilename(username);
    ifstream file(filename);

    if (!file.is_open()) {
        score = Score();
        return;
    }

    file >> score.wins >> score.losses >> score.draws;
    file.close();
}

void GameManager::saveScore(const string& username, const Score& score) {
    string filename = getScoreFilename(username);
    ofstream file(filename);
    if (file.is_open()) {
        file << score.wins << " " << score.losses << " " << score.draws;
        file.close();
    }
}

void GameManager::resetScore(const string& username) {
    string filename = getScoreFilename(username);
    ofstream file(filename);
    if (file.is_open()) {
        file << "0 0 0";
        file.close();
    }
}

const char* GameManager::choiceToString(char value) const {
    switch (value) {
        case 'r': return "ROCK";
        case 'p': return "PAPER";
        case 's': return "SCISSORS";
        default: return "UNKNOWN";
    }
}

int GameManager::determineResult(char you, char computer) const {
    if (you == computer) return 0;

    if ((you == 'r' && computer == 'p') ||
        (you == 's' && computer == 'r') ||
        (you == 'p' && computer == 's')) {
        return -1;
    }

    return 1;
}

void GameManager::playRPS(const string& username) {
    Score score;
    loadScore(username, score);

    if (!score.isZero()) {
        cout << "\n-------------------------\n   YOUR CURRENT SCORE\n-------------------------\n";
        cout << "Wins: " << score.wins << "\nLosses: " << score.losses << "\nDraws: " << score.draws << "\n";
        cout << "-------------------------\n";

        char choice;
        cout << "Do you want to RESET score? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            resetScore(username);
            score.reset();
            cout << "Score has been reset!\n";
        }
    }

    char playAgain;
    do {
        static mt19937 rng{random_device{}()};
        uniform_int_distribution<int> dist(0, 2);
        int n = dist(rng);
        char computer = (n == 0) ? 'r' : (n == 1 ? 'p' : 's');

        char you;
        cout << "\nEnter r for ROCK, p for PAPER and s for SCISSOR: ";
        cin >> you;

        if (you != 'r' && you != 'p' && you != 's') {
            cout << "Invalid choice! Please enter r, p, or s.\n";
            continue;
        }

        int result = determineResult(you, computer);

        if (result == 0) {
            cout << "\nGame Draw!\n";
            score.draws++;
        } else if (result == 1) {
            cout << "\nYou Won!\n";
            score.wins++;
        } else {
            cout << "\nYou Lost!\n";
            score.losses++;
        }

        saveScore(username, score);

        cout << "You chose: " << choiceToString(you)
                  << " | Computer chose: " << choiceToString(computer) << "\n";
        cout << "\n-------------------------\n   SCOREBOARD (Saved)\n-------------------------\n";
        cout << "Wins: " << score.wins
                  << "\nLosses: " << score.losses
                  << "\nDraws: " << score.draws << "\n";
        cout << "-------------------------\n";

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
}