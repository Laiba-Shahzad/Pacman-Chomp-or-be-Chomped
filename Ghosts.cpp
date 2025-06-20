#include "Ghosts.h"
#include <iostream>
using namespace std;

const float tileSize = 16.0f;
bool isFrightened = false;

Ghosts::Ghosts(int startX, int startY) : x(startX), y(startY)
{
    this->startX = startX;
    this->startY = startY;

    ghostTexture.create(7, 7);
    image.create(7, 7, sf::Color::Transparent);

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (i < 4 && (i - 3) * (i - 3) + (j - 3) * (j - 3) <= 9) {
                image.setPixel(j, i, sf::Color(255, 105, 180));
            }
            else if (i >= 4) {
                if ((j == 1 && i >= 5) || (j == 2 && i >= 4) ||
                    (j == 3 && i >= 5) || (j == 4 && i >= 4) ||
                    (j == 5 && i >= 5) || (j == 6 && i >= 4)) {
                    image.setPixel(j, i, sf::Color(255, 105, 180));
                }
            }
        }
    }

    image.setPixel(2, 2, sf::Color::White);
    image.setPixel(4, 2, sf::Color::White);
    image.setPixel(2, 3, sf::Color::Black);
    image.setPixel(4, 3, sf::Color::Black);

    ghostTexture.update(image);
    ghostSprite.setTexture(ghostTexture);

    sf::FloatRect bounds = ghostSprite.getLocalBounds();
    float scaleFactor = 1.4f;  // Smaller ghost
    float scaleX = (tileSize * scaleFactor) / bounds.width;
    float scaleY = (tileSize * scaleFactor) / bounds.height;
    ghostSprite.setScale(scaleX, scaleY);

    ghostSprite.setPosition(Vector2f(y * tileSize, x * tileSize));
}

Ghosts::~Ghosts() {}

int Ghosts::getX() { return x; }
int Ghosts::getY() { return y; }

void Ghosts::moves(char layout[maximum_rows][maximum_cols], int pacX, int pacY, int gx1, int gy1, int gx2, int gy2, int gx3, int gy3)
{
    int bestX = x;
    int bestY = y;

    int bestDist = isFrightened ? INT_MIN : INT_MAX;

    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (newX >= 0 && newX < maximum_rows && newY >= 0 && newY < maximum_cols &&
            layout[newX][newY] != '#' &&
            !(newX == gx1 && newY == gy1) &&
            !(newX == gx2 && newY == gy2) &&
            !(newX == gx3 && newY == gy3)) {

            int dist = abs(newX - pacX) + abs(newY - pacY);

            if (isFrightened) {
                if (dist > bestDist) {
                    bestDist = dist;
                    bestX = newX;
                    bestY = newY;
                }
            }
            else {
                if (dist < bestDist) {
                    bestDist = dist;
                    bestX = newX;
                    bestY = newY;
                }
            }
        }
    }

    if (bestX != x || bestY != y) {
        x = bestX;
        y = bestY;
        ghostSprite.setPosition(Vector2f(y * tileSize, x * tileSize));
    }
}

void Ghosts::setFrightened(bool value) {
    isFrightened = value;

    sf::Color ghostColor = value ? sf::Color(152, 255, 152) : sf::Color(255, 105, 180);

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (i < 4 && (i - 3) * (i - 3) + (j - 3) * (j - 3) <= 9) {
                image.setPixel(j, i, ghostColor);
            }
            else if (i >= 4) {
                if ((j == 1 && i >= 5) || (j == 2 && i >= 4) ||
                    (j == 3 && i >= 5) || (j == 4 && i >= 4) ||
                    (j == 5 && i >= 5) || (j == 6 && i >= 4)) {
                    image.setPixel(j, i, ghostColor);
                }
            }
        }
    }

    image.setPixel(2, 2, sf::Color::White);
    image.setPixel(4, 2, sf::Color::White);
    image.setPixel(2, 3, sf::Color::Black);
    image.setPixel(4, 3, sf::Color::Black);

    ghostTexture.update(image);
}

void Ghosts::reset() {
    x = startX;
    y = startY;
}

void Ghosts::draw(RenderWindow& window) {
    float scaleFactor = 1.4f;
    float offset = (tileSize - tileSize * scaleFactor) / 2.0f;
    ghostSprite.setPosition(Vector2f(y * tileSize + offset, x * tileSize + offset));
    window.draw(ghostSprite);
}



