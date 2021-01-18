#pragma once
#include <string>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "Game.h"


#define LEFT 'a'
#define RIGHT 'd' // Controls
#define UP 'w'
#define DOWN 's'

class Game;

class Player
{
public:
	Player(Game& game);
	virtual void behaviour() = 0;
	virtual ~Player() = default;
	int getX() { return _x; };
	int getY() { return _y; };
	bool isClearOFWall(char movement);
protected:
	char movement;
	int _x;
	int _y;
	Game& _game;
};

