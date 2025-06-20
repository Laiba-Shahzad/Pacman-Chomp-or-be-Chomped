#include <iostream>
#include "Game.h"
using namespace std;
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Game game;
    game.run();
    return 0;
}