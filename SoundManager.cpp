#include "SoundManager.h"
#include <iostream>
using namespace std;
using namespace sf;
SoundManager::SoundManager() {
    if (!chompBuf.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\pacman_chomp.wav")) {
        //cerr << "Failed to load pacman_chomp.wav\n";
    }
    if (!pelletBuf.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\own playing sound pt3.wav")) {
        //cerr << "Failed to load pellet.wav\n";
    }
    if (!deathBuf.loadFromFile("C:\\Users\\user\\source\\repos\\OOP Project Pacman\\pacman_death.wav")) {
        //cerr << "Failed to load death.wav\n";
    }

    chomp.setBuffer(chompBuf);
    pellet.setBuffer(pelletBuf);
    death.setBuffer(deathBuf);
}

void SoundManager::playChomp() {
    if (chomp.getStatus() == Sound::Playing) chomp.stop();
    chomp.play();
}

void SoundManager::playPellet() {
    if (pellet.getStatus() == Sound::Playing) pellet.stop();
    pellet.play();
}

void SoundManager::playDeath()
{
    if (death.getStatus() == Sound::Playing) death.stop();
    death.play();
}
void SoundManager::stopChomp() 
{
    chomp.stop();
}

void SoundManager::stopPellet() {
    pellet.stop();
}

void SoundManager::stopDeath() {
    death.stop();
}

