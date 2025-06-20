#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"Score.h"
#include"Game.h"
#include"FrontEnd.h"

using namespace sf;

class Pacman {
private:
    int row, col;
    float tileSize;
    ConvexShape shape;
    bool mouthOpen;
    float mouthTimer;
    int direction;

public:
    Pacman();
    Pacman(int startRow, int startCol, float tileSize);
    bool handleInput(Keyboard::Key key, Game& game, Score& score/*,Sound&chompSound,Sound &pelletSound*/, SoundManager& soundManager, FrontEnd& frontend);
    void update(float deltaTime);
    void draw(RenderWindow& window) const;
    int getRow() const;
    int getCol() const;
};