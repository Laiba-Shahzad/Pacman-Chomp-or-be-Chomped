#pragma once

#include<string>
using namespace std;
#include<fstream>

class Score
{
private:
    int value;

public:
    Score();

    void add(int points);
    int get() const;
    void reset();
    int loadHighScore(const string& filename);
    void saveHighScore(const string& filename, int score, int& highScore);
};


