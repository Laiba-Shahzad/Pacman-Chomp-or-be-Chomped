#pragma once
#include"Score.h"
#include <SFML/Graphics.hpp>
#include "SoundManager.h"
const int max_rows = 21;
const int max_cols = 80;
using namespace sf;
class Game
{
	int option;
	Font font;

public:

	Game();
	int rowsloaded;
	char gamelayout[max_rows][max_cols];
	Game(int opt);
	void loadgame(int opt);
	void displaygame();
	void run();


};