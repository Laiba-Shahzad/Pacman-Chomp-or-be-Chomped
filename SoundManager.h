#pragma once
#include <SFML/Audio.hpp>
using namespace sf;
class SoundManager 
{
    Sound chomp, pellet, death;
    SoundBuffer chompBuf, pelletBuf, deathBuf;

public:
    SoundManager();

    void playChomp();
    void playPellet();
    void playDeath();
    void stopChomp();
    void stopDeath();
    void stopPellet();
};
