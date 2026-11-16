#ifndef GAME_H
#define GAME_H

#include <string>
#include <random>

struct Score;

class GameManager {
private:
    std::mt19937 rng_;
    std::uniform_int_distribution<int> dist_;
    static std::string getScoreFilename(const std::string& username);
    void loadScore(const std::string& username, Score& score);
    void saveScore(const std::string& username, const Score& score);
    void resetScore(const std::string& username);
    const char* choiceToString(char value) const;
    int determineResult(char you, char computer) const;

public:
    GameManager();
    void playRPS(const std::string& username);
};

#endif // GAME_H