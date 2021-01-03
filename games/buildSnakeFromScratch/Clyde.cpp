#include "Clyde.h"

void Clyde::behaviour() 
{

	const int SLOWDOWN = 6;
	static int slowdown = SLOWDOWN;
	srand(time(0));
	if (slowdown == 0)
	{
		slowdown = SLOWDOWN;
		return;
	}

	const int arenaWidth = 40;
	const int arenaHeight = 17;

	bool clear = 0;
	while (!clear)
	{
		char dir[4] = { LEFT, RIGHT, UP, DOWN };
		movement = dir[rand() % 4];
		clear = isClearOFWall(movement);
	}

	switch (movement) {
	case LEFT:

		_x--;
		break;

	case RIGHT:

		_x++;
		break;
	case UP:

		_y--;

		break;

	case DOWN:

		_y++;

		break;

	}

	slowdown--;
}

