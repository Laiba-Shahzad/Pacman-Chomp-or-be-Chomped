#pragma once
#include <iostream>
#include<cstdlib>
#include<ctime>
#include <SFML/Graphics.hpp>
using namespace sf;
const int maximum_cols = 80;
const int maximum_rows = 21;
static Image image;
class Ghosts1
{
protected:
	enum direction { UP, DOWN, LEFT, RIGHT };
	const int dx[4] = { 0, 0, -1, 1 };
	const int dy[4] = { -1, 1, 0, 0 };
	
public:
	Ghosts1() {}
	virtual void moves(char layout[maximum_rows][maximum_cols], int pacX, int pacY, int gx1, int gy1, int gx2, int gy2, int gx3, int gy3) = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual void draw(RenderWindow& window) = 0;
	virtual void setFrightened(bool value)=0;
	virtual void reset() = 0;
	virtual ~Ghosts1() {}
};