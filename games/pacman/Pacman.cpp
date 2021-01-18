#include "Pacman.h"

void Pacman::behaviour()
{

	const int arenaWidth = 40;
	const int arenaHeight = 17;

	if (_kbhit()) {

		switch (_getch()) {

		case LEFT:
			movement = LEFT;
			break;

		case RIGHT:
			movement = RIGHT;
			break;

		case UP:
			movement = UP;
			break;

		case DOWN:
			movement = DOWN;
			break;

		}

	}

	bool clear = isClearOFWall(movement);

	if (clear)
	{
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
	}

}


