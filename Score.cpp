#include "Score.h"

Score::Score() : value(0) {}

void Score::add(int points) {
    value += points;
}

int Score::get() const {
    return value;
}

void Score::reset() {
    value = 0;
}

int Score:: loadHighScore(const string& filename)
{
    ifstream file(filename);
    int highScore = 0;

    if (file >> highScore)
        return highScore;

    return 0; 
}

void Score:: saveHighScore(const string & filename, int score, int& highScore) {
    if (score > highScore) {
        highScore = score;
        std::ofstream file(filename);
        if (file) {
            file << highScore;
        }
    }
}