#include "Game.h"
#include"Score.h"
#include <iostream>
#include<fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Ghosts.h"
#include "Pacman.h"
#include "Ghosts3.h"
#include "Ghosts2.h"
#include "Ghosts4.h"
#include "FrontEnd.h"
#include<SFML/Window.hpp>
using namespace sf;
using namespace std;

Game::Game()
{
    option = 0;
}

Game::Game(int opt)
{
    //cout << "Game constructor called" << endl;
    option = opt;

}
void Game::loadgame(int opt)
{
    option = opt;
    string filename;
    switch (option)
    {
    case 1:
        filename = "Dot Dungeon.txt";
        break;
    case 2:
        filename = "Pinky's Playground.txt";
        break;
    case 3:
        filename = "Ghostly Grid.txt";
        break;
    default:
        cout << "Invalid option" << endl;
        break;
    }
    ifstream file(filename);
    if (!file)
    {
        //cerr << "Could not open file: " << filename << endl;
        return;
    }
    string line;
    rowsloaded = 0;
    while (getline(file, line))
    {
        for (int i = 0; i < max_cols; ++i)
        {
            if (i < line.length())
                gamelayout[rowsloaded][i] = line[i];
            else
                gamelayout[rowsloaded][i] = ' ';
        }
        rowsloaded++;
    }
    file.close();
    //cout << "Game loaded successfully." << endl;
}
void Game::run()
{
    struct FloatingScore
    {
        Text text;
        Clock timer;
    };
    vector<FloatingScore> floatingScores;

    const float tileSize = 16.0f;

    FrontEnd frontEnd;
    frontEnd.loadSounds();

    if (!frontEnd.loadFont()) {
        //cerr << "Font failed to load. Exiting." << endl;
        return;
    }
    // SFML window
    sf::RenderWindow window(sf::VideoMode(max_cols * tileSize, max_rows * tileSize + 40), "Pacman");
    window.setFramerateLimit(60);
    frontEnd.loadFont(); // font is loaded for rendering text
    frontEnd.loadArenaTextures();

    frontEnd.showLoadingScreen(window);
    frontEnd.loadbackground(window);
    int selectedArena = frontEnd.showArenaSelectionScreen(window);

    loadgame(selectedArena);

     SoundManager soundManager;

    Score score2;
    int highScore = score2.loadHighScore("highscore.txt");
    int currentScore = 0;


    const int mapWidth = 80;
    const int mapHeight = rowsloaded;

    int pacmanRow = 19, pacmanCol = 39;
    bool foundP = false;
    for (int i = 0; i < rowsloaded; ++i) {
        for (int j = 0; j < max_rows; ++j) {
            if (gamelayout[i][j] == 'P') {
                pacmanRow = i;
                pacmanCol = j;
                foundP = true;
                break;
            }
        }
        if (foundP) break;
    }

    srand(static_cast<unsigned>(time(nullptr)));

    const int numOfGhosts = 4;
    Ghosts1* ghosts[4];
    ghosts[0] = new Ghosts(1, 2); // pink
    ghosts[1] = new Ghosts3(15, 10); // orange
    ghosts[2] = new Ghosts2(max_rows - 2, max_cols - 2); // cyan
    ghosts[3] = new Ghosts4(max_rows / 2, max_cols - 2); // red

    Pacman pacman(pacmanRow, pacmanCol, tileSize);
    Score score;

    Clock clock, moveClock, deltaClock;
    Clock frightenedClock;
    bool ghostsFrightened = false;
    bool gameOver = false;
    bool gameWon = false;

    Font font;
    font.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\arial.ttf");

    while (window.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if (!gameOver && !gameWon) {
            if (moveClock.getElapsedTime().asSeconds() > 0.1f) {
                bool becameFrightened = false;

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    becameFrightened = pacman.handleInput(sf::Keyboard::Up, *this, score , soundManager, frontEnd);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    becameFrightened = pacman.handleInput(sf::Keyboard::Down, *this, score, soundManager, frontEnd);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    becameFrightened = pacman.handleInput(sf::Keyboard::Left, *this, score , soundManager, frontEnd);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    becameFrightened = pacman.handleInput(sf::Keyboard::Right, *this, score, soundManager, frontEnd);
                }

                if (becameFrightened) {
                    ghostsFrightened = true;
                    frightenedClock.restart();
                    for (int i = 0; i < numOfGhosts; ++i)
                        ghosts[i]->setFrightened(true);
                }

                moveClock.restart();
            }


            if (ghostsFrightened && frightenedClock.getElapsedTime().asSeconds() >= 7.0f)
            {
                ghostsFrightened = false;
                for (int i = 0; i < numOfGhosts; ++i)
                    ghosts[i]->setFrightened(false);
                frontEnd.playArenaMusic();
            }

            float ghostSpeed = 0.2f;
            pacman.update(deltaTime);

            if (clock.getElapsedTime().asSeconds() > ghostSpeed) {
                for (int i = 0; i < numOfGhosts; ++i)
                    ghosts[i]->moves(gamelayout, pacman.getRow(), pacman.getCol(),
                        ghosts[(i + 1) % 4]->getX(), ghosts[(i + 1) % 4]->getY(),//avoiding overlapping with other ghosts
                        //diff stratergies for each ghosts
                        ghosts[(i + 2) % 4]->getX(), ghosts[(i + 2) % 4]->getY(),
                        ghosts[(i + 3) % 4]->getX(), ghosts[(i + 3) % 4]->getY());
                clock.restart();
            }


            int pRow = pacman.getCol(), pCol = pacman.getRow();
            for (int i = 0; i < numOfGhosts; ++i) {
                if (pRow == ghosts[i]->getY() && pCol == ghosts[i]->getX()) {
                    if (ghostsFrightened) {
                        
                        int gx = ghosts[i]->getY();
                        int gy = ghosts[i]->getX();
                        ghosts[i]->reset();

                        score.add(200);
                        FloatingScore fs;
                        fs.text.setFont(font);
                        fs.text.setCharacterSize(20);
                        fs.text.setFillColor(Color::Red);
                        fs.text.setString("200");
                        float x = gx * tileSize;
                        float y = gy * tileSize;
                        fs.text.setPosition(x, y);
                        fs.timer.restart();
                        floatingScores.push_back(fs);
						
                    }
                    else
                    {
                        gameOver = true;
                        /*deathSound.play();*/
                        soundManager.playDeath();
                    }
                }
            }


            bool pelletLeft = false;
            for (int i = 0; i < mapHeight && !pelletLeft; ++i) {
                for (int j = 0; j < mapWidth; ++j) {
                    if (gamelayout[i][j] == '.' || gamelayout[i][j] == 'o') {
                        pelletLeft = true;
                        break;
                    }
                }
            }
            if (!pelletLeft)
                gameWon = true;
        }


        window.clear(sf::Color::Black);
        for (int i = 0; i < mapHeight; ++i) {
            for (int j = 0; j < mapWidth; ++j) {
                float x = j * tileSize;
                float y = i * tileSize;

                if (gamelayout[i][j] == '#') {
                    sf::RectangleShape wall(sf::Vector2f(tileSize, tileSize));
                    wall.setPosition(x, y);
                    wall.setFillColor(sf::Color(0, 0, 255));
                    window.draw(wall);
                }
                else if (gamelayout[i][j] == '.') {
                    sf::CircleShape dot(tileSize / 4.0f);
                    dot.setPosition(x + tileSize / 2.0f - dot.getRadius(), y + tileSize / 2.0f - dot.getRadius());
                    dot.setFillColor(sf::Color::White);
                    window.draw(dot);
                }
                else if (gamelayout[i][j] == 'o') {
                    sf::CircleShape pellet(tileSize / 2.5f);
                    pellet.setPosition(x + tileSize / 2.0f - pellet.getRadius(), y + tileSize / 2.0f - pellet.getRadius());
                    pellet.setFillColor(sf::Color::Magenta);
                    window.draw(pellet);
                }
            }
        }

        // Draw entities
        ghosts[0]->draw(window);
        ghosts[1]->draw(window);
        ghosts[2]->draw(window);
        ghosts[3]->draw(window);
        pacman.draw(window);

        // Draw Score
        Text scoreText2;
        scoreText2.setFont(font);
        scoreText2.setCharacterSize(24);
        scoreText2.setPosition(max_cols * tileSize - 150, max_rows * tileSize);
        scoreText2.setFillColor(sf::Color::White);
        scoreText2.setString("Score: " + std::to_string(score.get()));
        window.draw(scoreText2);

        Text highScoreText;
        highScoreText.setFont(font);
        highScoreText.setString("High Score: " + std::to_string(highScore));
        highScoreText.setCharacterSize(24);
        highScoreText.setFillColor(sf::Color::Yellow);
        highScoreText.setPosition(4, max_rows * tileSize);
        window.draw(highScoreText);

        // Game Over / Win text
        if ((gameOver || gameWon) && !ghostsFrightened) {
            Text message;
            message.setFont(font);
            message.setCharacterSize(36);
            message.setFillColor(gameOver ? sf::Color::Red : sf::Color::Green);
            message.setStyle(sf::Text::Bold);
            message.setString(gameOver ? "Game Over!" : "You Win!");
            message.setPosition((max_cols * tileSize) / 2 - 100, (max_rows * tileSize) / 2);
            window.draw(message);
            window.display();


            sleep(seconds(1));

            break;
        }
        for (int i = 0; i < floatingScores.size(); ) {///////////////////
            if (floatingScores[i].timer.getElapsedTime().asSeconds() < 1.0f) {
                window.draw(floatingScores[i].text);
                ++i;
            }
            else {
                floatingScores.erase(floatingScores.begin() + i);
            }
        }
        window.display();
        score2.saveHighScore("highscore.txt", score.get(), highScore);
    }

    for (int i = 0; i < 4; i++)
        delete ghosts[i];

    int result = frontEnd.showEndScreen(window);
    if (result == 1)
    {
        frontEnd.stopArenaMusic();
        soundManager.stopChomp();
        soundManager.stopPellet();
        soundManager.stopDeath();

        frontEnd.stopArenaMusic();


        run();

    }
    else
    {
        window.close();
    }
}
void Game::displaygame()
{
  
    for (int i = 0; i < rowsloaded; ++i)
    {
        for (int j = 0; j < maximum_cols; ++j)
        {
            cout << gamelayout[i][j];
        }
        cout << endl;
    }
}