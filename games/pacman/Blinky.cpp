#include "Blinky.h"
#include <time.h>
void Blinky::behaviour()
{
	const int SLOWDOWN = 4;
	static int slowdown = SLOWDOWN;
	srand(time(0));
	if (slowdown == 0)
	{
		slowdown = SLOWDOWN;
		return;
	}

	const int arenaWidth = 40;
	const int arenaHeight = 17;

	if (_pm->getX() < _x && _pm->getY() < _y)
	{
		int res = rand() % 2;
		if(res ==1 && _game._board[_x][_y-1] != _game.WALL && isClearOFWall(UP))
		{
			movement = UP;
		}
		else if(isClearOFWall(LEFT))
		{
			movement = LEFT;
		}
	}
	if (_pm->getX() > _x && _pm->getY() < _y)
	{
		int res = rand() % 2;
		if (res == 1 && _game._board[_x][_y - 1] != _game.WALL && isClearOFWall(UP))
		{
			movement = UP;
		}
		else if (isClearOFWall(RIGHT))
		{
			movement = RIGHT;
		}
	}
	if (_pm->getX() < _x && _pm->getY() > _y)
	{
		int res = rand() % 2;
		if (res == 1 && _game._board[_x][_y +1] != _game.WALL && isClearOFWall(DOWN))
		{
			movement = DOWN;
		}
		else if (isClearOFWall(RIGHT))
		{
			movement = RIGHT;
		}
	}
	if (_pm->getX() > _x && _pm->getY() < _y)
	{
		int res = rand() % 2;
		if (res == 1 && _game._board[_x][_y - 1] != _game.WALL && isClearOFWall(UP))
		{
			movement = UP;
		}
		else if (isClearOFWall(RIGHT))
		{
			movement = RIGHT;
		}
	}
	else if (_pm->getX() > _x && _pm->getY() > _y)
	{
		int res = rand() % 2;
		if (res == 1 && isClearOFWall(DOWN))
		{
			movement = DOWN;
		}
		else if(isClearOFWall(RIGHT))
		{
			movement = RIGHT;
		}
	}

	else
	{
		if (_pm->getX() > _x && isClearOFWall(RIGHT))
			movement = RIGHT;
		else if (_pm->getX() < _x && isClearOFWall(LEFT))
			movement = LEFT;

		else if (_pm->getY() < _y && isClearOFWall(UP))
			movement = UP;


		else if (_pm->getY() > _y && isClearOFWall(DOWN))
			movement = DOWN;
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

