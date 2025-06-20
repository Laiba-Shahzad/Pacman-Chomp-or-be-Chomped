#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<SFML/Window.hpp>
using namespace sf;
class FrontEnd
{
    Font font;
    Texture dotDungeonTexture;
    Texture pinkysPlaygroundTexture;
    Texture ghostlyGridTexture;
    Sprite dotDungeonSprite;
    Sprite pinkysPlaygroundSprite;
    Sprite ghostlyGridSprite;
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Texture loadingImageTexture;
    Sprite loadingImageSprite;
    SoundBuffer loadingSoundBuffer;
    Sound loadingSound;
    SoundBuffer arenaSoundBuffer;
    Sound arenaSound;

public:

    FrontEnd();
    bool loadFont();
    void loadArenaTextures();
    void showLoadingScreen(RenderWindow& window);
    int showArenaSelectionScreen(RenderWindow& window);
    void loadgame(int option);
    void loadbackground(RenderWindow& window);
    bool loadSounds();
    int showEndScreen(RenderWindow& window);
    void stopArenaMusic();
    void playArenaMusic();

};





