#include "FrontEnd.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include"Game.h"
using namespace std;
using namespace sf;
FrontEnd::FrontEnd()
{

}
bool FrontEnd::loadFont()
{
    if (!font.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\arial.ttf")) {
        //cout << "Error loading font!" << endl;
        return false;
    }
    return true;
}

void FrontEnd::loadArenaTextures()
{
    ghostlyGridTexture.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\2.png");
    if (!dotDungeonTexture.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\2.png")) {
        //cerr << "Error loading Ghostly Grid arena!" << std::endl;
    }
    ghostlyGridSprite.setTexture(ghostlyGridTexture);
    ghostlyGridSprite.setScale(0.5f, 0.5f);
    ghostlyGridSprite.setPosition(550, 300);

    dotDungeonTexture.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\1.png");
    if (!dotDungeonTexture.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\1.png")) {
        //cerr << "Error loading Dot Dungeon arena!" << std::endl;
    }
    dotDungeonSprite.setTexture(dotDungeonTexture);
    dotDungeonSprite.setScale(0.5f, 0.5f);
    dotDungeonSprite.setPosition(325, 300);
    pinkysPlaygroundTexture.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\3.png");
    if (!pinkysPlaygroundTexture.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\3.png")) {
        //cerr << "Error loading Pinky's Playground arena!" << std::endl;
    }
    pinkysPlaygroundSprite.setTexture(pinkysPlaygroundTexture);
    pinkysPlaygroundSprite.setScale(0.5f, 0.5f);
    pinkysPlaygroundSprite.setPosition(325, 300);


}
void FrontEnd::loadbackground(RenderWindow& window)
{
    if (!backgroundTexture.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\arena background final.png"))
    {
        //cout << "Error loading background image!" << endl;
        return;
    }

    backgroundSprite.setTexture(backgroundTexture);

    // Calculate scale factors to fit the window in landscape mode
    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;

    // Use the larger scale to cover entire background (avoid borders)
    float uniformScale = std::max(scaleX, scaleY);

    backgroundSprite.setScale(uniformScale, uniformScale);
    backgroundSprite.setPosition(0, 0);  // Top-left corner


}

void FrontEnd::showLoadingScreen(RenderWindow& window)
{

    if (!loadingImageTexture.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\White Green Minimalist Landscape Illustration Group Project Presentation.png"))
    {
        //cout << "Error loading loading screen image!" << endl;
    }
    loadingImageSprite.setTexture(loadingImageTexture);
    loadingImageSprite.setScale(0.5f, 0.5f);
    loadingImageSprite.setPosition(
        (window.getSize().x - loadingImageSprite.getGlobalBounds().width) / 2,
        (window.getSize().y - loadingImageSprite.getGlobalBounds().height) / 2 - 20
    );
    loadingSound.play();
    Clock clock;
    while (clock.getElapsedTime().asSeconds() < 3.0f)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(loadingImageSprite);

        window.display();

    }
    loadingSound.stop();
}

int FrontEnd::showArenaSelectionScreen(RenderWindow& window)
{
    arenaSound.play();
    // Scale sprites to fit side by side
    float scale = 0.15f;
    dotDungeonSprite.setScale(scale, scale);
    pinkysPlaygroundSprite.setScale(scale, scale);
    ghostlyGridSprite.setScale(scale, scale);


    float spriteY = 130;
    float spacing = 50;  // space between sprites
    float spriteWidth = dotDungeonSprite.getGlobalBounds().width;

    // Calculate starting X to center all 3 with spacing
    float totalWidth = spriteWidth * 3 + spacing * 2;
    float startX = (window.getSize().x - totalWidth) / 2;

    dotDungeonSprite.setPosition(startX, spriteY);
    pinkysPlaygroundSprite.setPosition(startX + spriteWidth + spacing, spriteY);
    ghostlyGridSprite.setPosition(startX + 2 * (spriteWidth + spacing), spriteY);


    RectangleShape borders[3];
    Sprite* sprites[3] = { &dotDungeonSprite, &pinkysPlaygroundSprite, &ghostlyGridSprite };

    for (int i = 0; i < 3; ++i) {
        borders[i].setSize(Vector2f(sprites[i]->getGlobalBounds().width, sprites[i]->getGlobalBounds().height));
        borders[i].setOutlineThickness(4);
        borders[i].setOutlineColor(Color::Transparent);
        borders[i].setFillColor(Color::Transparent);
    }

    // Arena labels
    Text labels[3];
    string names[] = { "Dot Dungeon", "Pinky's Playground", "Ghostly Grid" };
    for (int i = 0; i < 3; ++i) {
        labels[i].setFont(font);
        labels[i].setString(names[i]);
        labels[i].setCharacterSize(20);
        labels[i].setFillColor(Color::Yellow);
        FloatRect bounds = sprites[i]->getGlobalBounds();
        labels[i].setPosition(
            bounds.left + bounds.width / 2 - labels[i].getLocalBounds().width / 2,
            bounds.top + bounds.height + 10
        );
    }

    while (window.isOpen())
    {
        Vector2i mousePos = Mouse::getPosition(window);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                for (int i = 0; i < 3; ++i) {
                    if (sprites[i]->getGlobalBounds().contains((Vector2f)mousePos)) {
                        //cout << "Arena " << i + 1 << " selected!" << endl;
                        return i + 1;
                    }
                }
            }
        }

        // Hover effect
        for (int i = 0; i < 3; ++i)
        {
            if (sprites[i]->getGlobalBounds().contains((Vector2f)mousePos))
                borders[i].setOutlineColor(Color::Red);
            else
                borders[i].setOutlineColor(Color::Transparent);

            borders[i].setPosition(sprites[i]->getPosition());
        }

        window.clear();

        window.draw(backgroundSprite); // Draw the background
        for (int i = 0; i < 3; ++i) {
            window.draw(*sprites[i]);
            window.draw(borders[i]);
            window.draw(labels[i]);
        }

        window.display();
    }
    arenaSound.stop();
    return 0;
}
void FrontEnd::loadgame(int arena)
{
    Game game;
    game.loadgame(arena);

}
bool FrontEnd::loadSounds()
{

    if (!loadingSoundBuffer.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\mixkit-mysterious-long-swell-2671.wav"))
    {
        //cout << "Error loading loading screen sound!" << endl;
        return false;
    }
    loadingSound.setBuffer(loadingSoundBuffer);
    loadingSound.setLoop(false); // Play once

    if (!arenaSoundBuffer.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\game-music-loop-6-144641 (1).mp3"))
    {
        //cout << "Error loading arena selection sound!" << endl;
        return false;
    }
    arenaSound.setBuffer(arenaSoundBuffer);


    return true;
}
int FrontEnd::showEndScreen(sf::RenderWindow& window) {
    //loading screen background(final screen)
    Texture bgTexture;
    if (!bgTexture.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\pacman exit display.png"))
    {
        //cout << "Failed to load end background\n";
        return -1;
    }
    Sprite bgSprite(bgTexture);
    float scaleX = (float)window.getSize().x / bgTexture.getSize().x;
    float scaleY = (float)window.getSize().y / bgTexture.getSize().y;
    float uniformScale = std::max(scaleX, scaleY);
    bgSprite.setScale(uniformScale, uniformScale);
    bgSprite.setPosition(0, 0);

    // Loading replay and exit images
    sf::Texture replayTexture, exitTexture;
    if (!replayTexture.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\replay.png") ||
        !exitTexture.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\exit.png"))
    {
        //cout << "Failed to load replay or exit image\n";
        return -1;
    }

    Sprite replaySprite(replayTexture);
    Sprite exitSprite(exitTexture);


    float btnScale = 0.75f;
    replaySprite.setScale(btnScale, btnScale);
    exitSprite.setScale(btnScale, btnScale);


    float centerX = window.getSize().x / 2.0f;
    float centerY = window.getSize().y / 2.0f;


    float spacing = 40.0f;
    float replayHeight = replaySprite.getGlobalBounds().height;
    float exitHeight = exitSprite.getGlobalBounds().height;

    replaySprite.setPosition(centerX - replaySprite.getGlobalBounds().width / 2,
        centerY - replayHeight - spacing / 2 + 85);
    exitSprite.setPosition(centerX - exitSprite.getGlobalBounds().width / 2,
        centerY + spacing / 2 + 77);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);//using int vector
                if (replaySprite.getGlobalBounds().contains((Vector2f)mousePos))//using sfml vector
                    return 1; // Replay
                if (exitSprite.getGlobalBounds().contains((Vector2f)mousePos))
                    return 0; // Exit
            }
        }

        window.clear();
        window.draw(bgSprite);
        window.draw(replaySprite);
        window.draw(exitSprite);
        window.display();
    }

    return 0; // Exits if window closes
}
void FrontEnd::stopArenaMusic()
{
    arenaSound.stop();
}
void FrontEnd::playArenaMusic()
{
    arenaSound.play();
}
