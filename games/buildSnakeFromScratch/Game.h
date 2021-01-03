#pragma once

#include "Player.h"



class Game
{
public:


	Game();
	char _board[17][40];
	

	friend class Player;
	friend class Blinky; // access consts 
	friend class Pacman;
	friend class Clyde;
private:
	const int arenaWidth = 17;
	const int arenaHeight = 40;
	const char EDIBLE = '\'';
	const char  WALL = '+';
	
};

